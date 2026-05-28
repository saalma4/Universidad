import time
from dataclasses import dataclass

try:
    import pybullet as p
    import tkinter as tk
    from tkinter import ttk, messagebox
except ImportError as e:
    print("Falta una libreria necesaria:", e)
    print("Instala pybullet y ejecuta de nuevo.")
    raise

G = 9.81
SIM_DT = 1.0 / 1000.0
PURE_ROLLING_REL_TOL = 0.01
STOP_SPEED = 0.01


@dataclass
class Parameters:
    mass: float = 6.80
    radius: float = 0.109
    mu: float = 0.3
    v0: float = 4.0
    lane_length: float = 20.0
    launch_height: float = 0.111
    time_scale: float = 0.5

    @property
    def beta(self) -> float:
        return 2.0 / 5.0

    @property
    def inertia(self) -> float:
        return self.beta * self.mass * self.radius ** 2


def compute_theory(params: Parameters):
    t_star = 2.0 * params.v0 / (7.0 * params.mu * G)
    x_star = 12.0 * params.v0 ** 2 / (49.0 * params.mu * G)
    v_star = 5.0 * params.v0 / 7.0
    omega_star = v_star / params.radius
    return {
        "t_star": t_star,
        "x_star": x_star,
        "v_star": v_star,
        "omega_star": omega_star,
    }


class BowlingSimulation:
    def __init__(self, params: Parameters):
        self.params = params
        self.client = p.connect(p.GUI)
        self.ball_id = None
        self.ground_id = None

        self.sim_time = 0.0
        self.ball_launched = False
        self.running = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = compute_theory(self.params)

        self.mark_a_id = -1
        self.mark_b_id = -1
        self.state_text_id = -1
        self.current_color = None

        self.wall_last = time.perf_counter()
        self.accumulator = 0.0
        self.cam_x = 2.5

        self.reset_world()

    def close(self):
        if self.client is not None:
            p.disconnect(self.client)
            self.client = None

    def state_color(self, regime):
        if regime == "Deslizamiento":
            return [0.95, 0.40, 0.12, 1.0]
        if regime == "Rodadura pura":
            return [0.10, 0.72, 0.18, 1.0]
        if regime == "Parada":
            return [0.55, 0.55, 0.55, 1.0]
        return [0.55, 0.55, 0.55, 1.0]

    def update_ball_visuals(self, pos, orn, regime):
        color = self.state_color(regime)
        if color != self.current_color:
            p.changeVisualShape(self.ball_id, -1, rgbaColor=color, physicsClientId=self.client)
            self.current_color = color

        r = self.params.radius * 1.18
        tip_a = p.multiplyTransforms(pos, orn, [r, 0.0, 0.0], [0, 0, 0, 1])[0]
        tip_b = p.multiplyTransforms(pos, orn, [0.0, 0.0, r], [0, 0, 0, 1])[0]

        self.mark_a_id = p.addUserDebugLine(
            pos, tip_a, [1, 1, 1], 2, 0,
            replaceItemUniqueId=self.mark_a_id,
            physicsClientId=self.client
        )
        self.mark_b_id = p.addUserDebugLine(
            pos, tip_b, [0, 0, 0], 2, 0,
            replaceItemUniqueId=self.mark_b_id,
            physicsClientId=self.client
        )
        text_pos = [pos[0], pos[1], pos[2] + self.params.radius + 0.08]
        self.state_text_id = p.addUserDebugText(
            regime, text_pos, [0, 0, 0], 0.95, 0,
            replaceItemUniqueId=self.state_text_id,
            physicsClientId=self.client
        )

    def reset_world(self):
        self.sim_time = 0.0
        self.ball_launched = False
        self.running = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = compute_theory(self.params)
        self.mark_a_id = -1
        self.mark_b_id = -1
        self.state_text_id = -1
        self.current_color = None
        self.wall_last = time.perf_counter()
        self.accumulator = 0.0
        self.cam_x = 2.5

        p.resetSimulation(physicsClientId=self.client)
        p.setGravity(0, 0, -G, physicsClientId=self.client)
        p.setTimeStep(SIM_DT, physicsClientId=self.client)
        p.setPhysicsEngineParameter(fixedTimeStep=SIM_DT, numSolverIterations=300, physicsClientId=self.client)
        p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0, physicsClientId=self.client)

        half_len = self.params.lane_length / 2.0
        shape = p.createCollisionShape(p.GEOM_BOX, halfExtents=[half_len, 0.6, 0.02], physicsClientId=self.client)
        visual = p.createVisualShape(
            p.GEOM_BOX, halfExtents=[half_len, 0.6, 0.02],
            rgbaColor=[0.82, 0.72, 0.52, 1], physicsClientId=self.client
        )
        self.ground_id = p.createMultiBody(
            baseMass=0,
            baseCollisionShapeIndex=shape,
            baseVisualShapeIndex=visual,
            basePosition=[half_len, 0, -0.02],
            physicsClientId=self.client
        )
        p.changeDynamics(
            self.ground_id, -1,
            lateralFriction=self.params.mu,
            rollingFriction=0.0,
            spinningFriction=0.0,
            restitution=0.0,
            physicsClientId=self.client
        )

        cs = p.createCollisionShape(p.GEOM_SPHERE, radius=self.params.radius, physicsClientId=self.client)
        vs = p.createVisualShape(
            p.GEOM_SPHERE, radius=self.params.radius,
            rgbaColor=[0.08, 0.08, 0.12, 1],
            physicsClientId=self.client
        )
        self.ball_id = p.createMultiBody(
            baseMass=self.params.mass,
            baseCollisionShapeIndex=cs,
            baseVisualShapeIndex=vs,
            basePosition=[0.0, 0.0, self.params.launch_height],
            physicsClientId=self.client
        )
        p.changeDynamics(
            self.ball_id, -1,
            lateralFriction=self.params.mu,
            rollingFriction=0.0,
            spinningFriction=0.0,
            localInertiaDiagonal=[self.params.inertia] * 3,
            linearDamping=0.0,
            angularDamping=0.0,
            restitution=0.0,
            physicsClientId=self.client
        )

        p.resetDebugVisualizerCamera(
            cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
            cameraTargetPosition=[self.cam_x, 0.0, 0.0], physicsClientId=self.client
        )

    def launch_ball(self):
        self.sim_time = 0.0
        self.ball_launched = True
        self.running = True
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = compute_theory(self.params)
        self.wall_last = time.perf_counter()
        self.accumulator = 0.0

        p.resetBasePositionAndOrientation(
            self.ball_id, [0.0, 0.0, self.params.launch_height], [0, 0, 0, 1],
            physicsClientId=self.client
        )
        p.resetBaseVelocity(
            self.ball_id,
            linearVelocity=[self.params.v0, 0.0, 0.0],
            angularVelocity=[0.0, 0.0, 0.0],
            physicsClientId=self.client
        )

    def current_state(self):
        pos, orn = p.getBasePositionAndOrientation(self.ball_id, physicsClientId=self.client)
        lin_vel, ang_vel = p.getBaseVelocity(self.ball_id, physicsClientId=self.client)
        vx = lin_vel[0]
        omega = ang_vel[1]
        slip = vx - self.params.radius * omega
        speed_ref = max(abs(vx), abs(self.params.radius * omega), 1e-6)
        pure = abs(slip) / speed_ref <= PURE_ROLLING_REL_TOL

        regime = "En espera"
        if self.ball_launched:
            if abs(vx) <= STOP_SPEED and abs(omega) <= STOP_SPEED / max(self.params.radius, 1e-9):
                regime = "Parada"
            elif pure:
                regime = "Rodadura pura"
            else:
                regime = "Deslizamiento"

        return {
            "pos": pos,
            "orn": orn,
            "vx": vx,
            "omega": omega,
            "slip": slip,
            "pure": pure,
            "regime": regime,
        }

    def step_until_now(self):
        now = time.perf_counter()
        elapsed = (now - self.wall_last) * max(self.params.time_scale, 0.0)
        self.wall_last = now
        self.accumulator += min(elapsed, 0.1)

        max_steps = 200
        steps = 0
        while self.accumulator >= SIM_DT and steps < max_steps:
            p.stepSimulation(physicsClientId=self.client)
            if self.running and self.ball_launched:
                self.sim_time += SIM_DT
            self.accumulator -= SIM_DT
            steps += 1

        state = self.current_state()

        if self.ball_launched and not self.reached_rolling and state["pure"]:
            self.reached_rolling = True
            self.rolling_time = self.sim_time
            self.rolling_speed = state["vx"]
            self.rolling_omega = state["omega"]

        self.update_ball_visuals(state["pos"], state["orn"], state["regime"])

        target_x = max(2.0, state["pos"][0] + 1.5)
        self.cam_x += 0.10 * (target_x - self.cam_x)
        p.resetDebugVisualizerCamera(
            cameraDistance=4.0,
            cameraYaw=0,
            cameraPitch=-18,
            cameraTargetPosition=[self.cam_x, 0.0, 0.0],
            physicsClientId=self.client
        )

        return {
            "t": self.sim_time,
            "x": state["pos"][0],
            "vx": state["vx"],
            "omega": state["omega"],
            "wR": state["omega"] * self.params.radius,
            "slip": state["slip"],
            "regime": state["regime"],
            "rolling_time": self.rolling_time,
            "rolling_speed": self.rolling_speed,
            "rolling_omega": self.rolling_omega,
            "t_theory": self.theory["t_star"],
            "v_theory": self.theory["v_star"],
        }


class BowlingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Apartado 2 - Simulacion base")
        self.root.geometry("760x740")
        self.vars = {}
        self.theory_labels = {}
        self.sim_labels = {}

        self.sim = BowlingSimulation(self.defaults())
        self.build_ui()
        self.update_theory(self.sim.theory)
        self.root.after(10, self.update_loop)
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

    def defaults(self):
        return Parameters()

    def build_ui(self):
        main = ttk.Frame(self.root, padding=12)
        main.pack(fill="both", expand=True)

        ttk.Label(main, text="Apartado 2 · comprobacion de la teoria", font=("Segoe UI", 13, "bold")).pack(anchor="w", pady=(0, 10))

        frame = ttk.LabelFrame(main, text="Variables", padding=10)
        frame.pack(fill="x", pady=(0, 10))
        fields = [
            ("mass", "Masa (kg)"),
            ("radius", "Radio (m)"),
            ("mu", "Rozamiento mu"),
            ("v0", "Velocidad inicial v0 (m/s)"),
            ("lane_length", "Longitud pista (m)"),
            ("launch_height", "Altura salida (m)"),
            ("time_scale", "Escala temporal"),
        ]
        values = self.defaults().__dict__
        for i, (key, label) in enumerate(fields):
            ttk.Label(frame, text=label).grid(row=i, column=0, sticky="w", pady=4)
            var = tk.StringVar(value=str(values[key]))
            ttk.Entry(frame, textvariable=var, width=16).grid(row=i, column=1, sticky="w", pady=4, padx=(8, 0))
            self.vars[key] = var

        buttons = ttk.Frame(main)
        buttons.pack(fill="x", pady=(0, 10))
        ttk.Button(buttons, text="Aplicar", command=self.apply_parameters).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Lanzar", command=self.launch).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Reset", command=self.reset).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Valores por defecto", command=self.load_defaults).pack(side="left")

        theory_frame = ttk.LabelFrame(main, text="Teoria", padding=10)
        theory_frame.pack(fill="x", pady=(0, 10))
        for i, (key, label) in enumerate([
            ("t_star", "Tiempo teorico t* (s)"),
            ("x_star", "Distancia teorica x* (m)"),
            ("v_star", "Velocidad teorica v* (m/s)"),
            ("omega_star", "Omega teorica (rad/s)"),
        ]):
            ttk.Label(theory_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(theory_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.theory_labels[key] = lbl

        sim_frame = ttk.LabelFrame(main, text="Simulacion", padding=10)
        sim_frame.pack(fill="x")
        for i, (key, label) in enumerate([
            ("regime", "Estado"),
            ("t", "Tiempo (s)"),
            ("x", "Posicion x (m)"),
            ("vx", "Velocidad lineal (m/s)"),
            ("omega", "Velocidad angular (rad/s)"),
            ("wR", "omega·R (m/s)"),
            ("slip", "Slip v - Rω (m/s)"),
            ("rolling_time", "Instante medido de rodadura (s)"),
            ("rolling_speed", "Velocidad medida en rodadura (m/s)"),
            ("error_t", "Error relativo en t* (%)"),
            ("error_v", "Error relativo en v* (%)"),
        ]):
            ttk.Label(sim_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(sim_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.sim_labels[key] = lbl

        ttk.Label(
            main,
            text="La bola cambia de color segun el estado y lleva dos marcas radiales para ver mejor la rotacion.",
        ).pack(anchor="w", pady=(12, 0))

        self.load_defaults()

    def parse_params(self):
        try:
            params = Parameters(
                mass=float(self.vars["mass"].get()),
                radius=float(self.vars["radius"].get()),
                mu=float(self.vars["mu"].get()),
                v0=float(self.vars["v0"].get()),
                lane_length=float(self.vars["lane_length"].get()),
                launch_height=float(self.vars["launch_height"].get()),
                time_scale=float(self.vars["time_scale"].get()),
            )
        except ValueError:
            raise ValueError("Todos los valores deben ser numericos.")
        if params.mass <= 0 or params.radius <= 0 or params.mu <= 0 or params.v0 < 0 or params.lane_length <= 0 or params.time_scale <= 0:
            raise ValueError("Revisa los valores de entrada.")
        return params

    def update_theory(self, theory):
        for k, lbl in self.theory_labels.items():
            lbl.config(text=f"{theory[k]:.4f}")

    def load_defaults(self):
        params = self.defaults()
        for key, value in params.__dict__.items():
            self.vars[key].set(str(value))
        self.update_theory(compute_theory(params))

    def apply_parameters(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.sim.params = params
        self.sim.theory = compute_theory(params)
        self.update_theory(self.sim.theory)

    def launch(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.sim.params = params
        self.sim.launch_ball()
        self.update_theory(self.sim.theory)

    def reset(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.sim.params = params
        self.sim.reset_world()
        self.update_theory(self.sim.theory)
        for lbl in self.sim_labels.values():
            lbl.config(text="-")
        self.sim_labels["regime"].config(text="En espera")

    def update_loop(self):
        if self.sim is not None and self.sim.client is not None:
            data = self.sim.step_until_now()
            self.refresh_telemetry(data)
        self.root.after(10, self.update_loop)

    def refresh_telemetry(self, data):
        self.sim_labels["regime"].config(text=data["regime"])
        self.sim_labels["t"].config(text=f"{data['t']:.4f}")
        self.sim_labels["x"].config(text=f"{data['x']:.4f}")
        self.sim_labels["vx"].config(text=f"{data['vx']:.4f}")
        self.sim_labels["omega"].config(text=f"{data['omega']:.4f}")
        self.sim_labels["wR"].config(text=f"{data['wR']:.4f}")
        self.sim_labels["slip"].config(text=f"{data['slip']:.6f}")
        self.sim_labels["rolling_time"].config(text="-" if data["rolling_time"] is None else f"{data['rolling_time']:.4f}")
        self.sim_labels["rolling_speed"].config(text="-" if data["rolling_speed"] is None else f"{data['rolling_speed']:.4f}")
        if data["rolling_time"] is not None:
            err_t = 100.0 * abs(data["rolling_time"] - data["t_theory"]) / max(data["t_theory"], 1e-9)
            err_v = 100.0 * abs(data["rolling_speed"] - data["v_theory"]) / max(abs(data["v_theory"]), 1e-9)
            self.sim_labels["error_t"].config(text=f"{err_t:.4f}")
            self.sim_labels["error_v"].config(text=f"{err_v:.4f}")
        else:
            self.sim_labels["error_t"].config(text="-")
            self.sim_labels["error_v"].config(text="-")

    def on_close(self):
        if self.sim is not None:
            self.sim.close()
        self.root.destroy()


def main():
    root = tk.Tk()
    try:
        ttk.Style(root).theme_use("clam")
    except Exception:
        pass
    BowlingApp(root)
    root.mainloop()


if __name__ == "__main__":
    main()
