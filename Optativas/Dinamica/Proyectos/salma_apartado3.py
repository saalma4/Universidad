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
    v0: float = 4.0
    omega0: float = 25.0
    beta_real: float = 0.34
    mu_front: float = 0.16
    mu_back: float = 0.35
    oil_length: float = 12.19
    mu_rolling: float = 0.0
    lane_length: float = 20.0
    launch_height: float = 0.111
    time_scale: float = 0.5
    mu_ideal: float = 0.18

    @property
    def beta_ideal(self) -> float:
        return 2.0 / 5.0

    @property
    def inertia_real(self) -> float:
        return self.beta_real * self.mass * self.radius ** 2


def theory_general(v0, omega0, radius, mu, beta):
    s0 = v0 - radius * omega0
    if mu <= 0:
        return {"t_star": float("inf"), "v_star": v0, "omega_star": omega0, "x_star": float("inf")}
    if abs(s0) < 1e-12:
        return {"t_star": 0.0, "v_star": v0, "omega_star": v0 / radius, "x_star": 0.0}

    t_star = beta * abs(s0) / ((1.0 + beta) * mu * G)
    sign = 1.0 if s0 > 0 else -1.0
    v_star = v0 - sign * mu * G * t_star
    omega_star = v_star / radius
    x_star = v0 * t_star - 0.5 * sign * mu * G * t_star ** 2
    return {"t_star": t_star, "v_star": v_star, "omega_star": omega_star, "x_star": x_star}


def theory_piecewise(params: Parameters):
    """Estimación teórica por tramos: zona aceitada y zona seca."""
    t1 = theory_general(params.v0, params.omega0, params.radius, max(params.mu_front, 1e-12), params.beta_real)

    if t1["x_star"] <= params.oil_length:
        return {
            "t_star": t1["t_star"],
            "v_star": t1["v_star"],
            "omega_star": t1["omega_star"],
            "x_star": t1["x_star"],
            "zone": "Zona aceitada",
        }

    s0 = params.v0 - params.radius * params.omega0
    sign = 1.0 if s0 > 0 else -1.0
    a1 = sign * params.mu_front * G
    alpha1 = a1 / (params.beta_real * params.radius)

    # Estado al salir de la zona aceitada
    disc_t = params.oil_length
    v_mid = params.v0 - a1 * disc_t / max(params.v0 + t1["v_star"], 1e-9)  # fallback simple if needed
    # cálculo correcto usando ecuación horaria según signo
    # x = v0*t - 0.5*a*t^2 con a = sign*mu*G
    # Resolver 0.5*a*t^2 - v0*t + x = 0
    if abs(a1) < 1e-12:
        t_mid = params.oil_length / max(params.v0, 1e-9)
    else:
        A = 0.5 * a1
        B = -params.v0
        C = params.oil_length
        disc = B * B - 4.0 * A * C
        disc = max(disc, 0.0)
        sqrt_disc = disc ** 0.5
        roots = []
        for cand in [(-B - sqrt_disc) / (2.0 * A), (-B + sqrt_disc) / (2.0 * A)]:
            if cand >= 0:
                roots.append(cand)
        t_mid = min(roots) if roots else 0.0
    v_mid = params.v0 - a1 * t_mid
    omega_mid = params.omega0 + (sign * params.mu_front * G / (params.beta_real * params.radius)) * t_mid

    t2 = theory_general(v_mid, omega_mid, params.radius, max(params.mu_back, 1e-12), params.beta_real)
    return {
        "t_star": t_mid + t2["t_star"],
        "v_star": t2["v_star"],
        "omega_star": t2["omega_star"],
        "x_star": params.oil_length + t2["x_star"],
        "zone": "Zona seca",
    }


class BowlingSimulation:
    def __init__(self, params: Parameters):
        self.params = params
        self.client = p.connect(p.GUI)
        self.ball_id = None
        self.front_id = None
        self.back_id = None

        self.running = False
        self.ball_launched = False
        self.reached_rolling = False
        self.sim_time = 0.0
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = theory_piecewise(self.params)

        self.mark_a_id = -1
        self.mark_b_id = -1
        self.state_text_id = -1
        self.zone_text_id = -1
        self.current_color = None
        self.current_mu_applied = None

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
        return [0.10, 0.10, 0.12, 1.0]

    def update_ball_visuals(self, pos, orn, regime, zone):
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

        text_pos_1 = [pos[0], pos[1], pos[2] + self.params.radius + 0.08]
        text_pos_2 = [pos[0], pos[1], pos[2] + self.params.radius + 0.16]

        self.state_text_id = p.addUserDebugText(
            regime, text_pos_1, [0, 0, 0], 0.95, 0,
            replaceItemUniqueId=self.state_text_id,
            physicsClientId=self.client
        )
        self.zone_text_id = p.addUserDebugText(
            zone, text_pos_2, [0, 0, 0], 0.9, 0,
            replaceItemUniqueId=self.zone_text_id,
            physicsClientId=self.client
        )

    def apply_ball_dynamics_for_zone(self, mu_now):
        if self.current_mu_applied is not None and abs(self.current_mu_applied - mu_now) < 1e-12:
            return
        p.changeDynamics(
            self.ball_id, -1,
            lateralFriction=mu_now,
            rollingFriction=self.params.mu_rolling,
            spinningFriction=0.0,
            localInertiaDiagonal=[self.params.inertia_real] * 3,
            linearDamping=0.0,
            angularDamping=0.0,
            restitution=0.0,
            physicsClientId=self.client
        )
        self.current_mu_applied = mu_now

    def reset_world(self):
        self.sim_time = 0.0
        self.running = False
        self.ball_launched = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = theory_piecewise(self.params)
        self.mark_a_id = -1
        self.mark_b_id = -1
        self.state_text_id = -1
        self.zone_text_id = -1
        self.current_color = None
        self.current_mu_applied = None
        self.wall_last = time.perf_counter()
        self.accumulator = 0.0
        self.cam_x = 2.5

        p.resetSimulation(physicsClientId=self.client)
        p.setGravity(0, 0, -G, physicsClientId=self.client)
        p.setTimeStep(SIM_DT, physicsClientId=self.client)
        p.setPhysicsEngineParameter(fixedTimeStep=SIM_DT, numSolverIterations=300, physicsClientId=self.client)
        p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0, physicsClientId=self.client)

        front_half = self.params.oil_length / 2.0
        back_len = max(self.params.lane_length - self.params.oil_length, 0.5)
        back_half = back_len / 2.0

        shape_front = p.createCollisionShape(p.GEOM_BOX, halfExtents=[front_half, 0.6, 0.02], physicsClientId=self.client)
        vis_front = p.createVisualShape(
            p.GEOM_BOX, halfExtents=[front_half, 0.6, 0.02],
            rgbaColor=[0.95, 0.85, 0.55, 1], physicsClientId=self.client
        )
        self.front_id = p.createMultiBody(
            baseMass=0,
            baseCollisionShapeIndex=shape_front,
            baseVisualShapeIndex=vis_front,
            basePosition=[front_half, 0, -0.02],
            physicsClientId=self.client
        )
        p.changeDynamics(
            self.front_id, -1,
            lateralFriction=self.params.mu_front,
            rollingFriction=self.params.mu_rolling,
            spinningFriction=0.0,
            restitution=0.0,
            physicsClientId=self.client
        )

        shape_back = p.createCollisionShape(p.GEOM_BOX, halfExtents=[back_half, 0.6, 0.02], physicsClientId=self.client)
        vis_back = p.createVisualShape(
            p.GEOM_BOX, halfExtents=[back_half, 0.6, 0.02],
            rgbaColor=[0.86, 0.86, 0.86, 1], physicsClientId=self.client
        )
        self.back_id = p.createMultiBody(
            baseMass=0,
            baseCollisionShapeIndex=shape_back,
            baseVisualShapeIndex=vis_back,
            basePosition=[self.params.oil_length + back_half, 0, -0.02],
            physicsClientId=self.client
        )
        p.changeDynamics(
            self.back_id, -1,
            lateralFriction=self.params.mu_back,
            rollingFriction=self.params.mu_rolling,
            spinningFriction=0.0,
            restitution=0.0,
            physicsClientId=self.client
        )

        cs = p.createCollisionShape(p.GEOM_SPHERE, radius=self.params.radius, physicsClientId=self.client)
        vs = p.createVisualShape(
            p.GEOM_SPHERE, radius=self.params.radius,
            rgbaColor=[0.10, 0.10, 0.12, 1],
            physicsClientId=self.client
        )
        self.ball_id = p.createMultiBody(
            baseMass=self.params.mass,
            baseCollisionShapeIndex=cs,
            baseVisualShapeIndex=vs,
            basePosition=[0.0, 0.0, self.params.launch_height],
            physicsClientId=self.client
        )
        self.apply_ball_dynamics_for_zone(self.params.mu_front)

        p.resetDebugVisualizerCamera(
            cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
            cameraTargetPosition=[self.cam_x, 0.0, 0.0], physicsClientId=self.client
        )

    def launch_ball(self):
        self.sim_time = 0.0
        self.running = True
        self.ball_launched = True
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = theory_piecewise(self.params)
        self.wall_last = time.perf_counter()
        self.accumulator = 0.0

        p.resetBasePositionAndOrientation(
            self.ball_id,
            [0.0, 0.0, self.params.launch_height],
            [0, 0, 0, 1],
            physicsClientId=self.client
        )
        self.apply_ball_dynamics_for_zone(self.params.mu_front)
        p.resetBaseVelocity(
            self.ball_id,
            linearVelocity=[self.params.v0, 0.0, 0.0],
            angularVelocity=[0.0, self.params.omega0, 0.0],
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

        if pos[0] < self.params.oil_length:
            zone = "Zona aceitada"
            mu_now = self.params.mu_front
        else:
            zone = "Zona seca"
            mu_now = self.params.mu_back

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
            "zone": zone,
            "mu_now": mu_now,
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
            state_before = self.current_state()
            self.apply_ball_dynamics_for_zone(state_before["mu_now"])
            p.stepSimulation(physicsClientId=self.client)
            if self.running and self.ball_launched:
                self.sim_time += SIM_DT
            self.accumulator -= SIM_DT
            steps += 1

        state = self.current_state()
        self.apply_ball_dynamics_for_zone(state["mu_now"])

        if self.ball_launched and not self.reached_rolling and state["pure"]:
            self.reached_rolling = True
            self.rolling_time = self.sim_time
            self.rolling_speed = state["vx"]
            self.rolling_omega = state["omega"]

        self.update_ball_visuals(state["pos"], state["orn"], state["regime"], state["zone"])

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
            "zone": state["zone"],
            "mu_now": state["mu_now"],
            "rolling_time": self.rolling_time,
            "rolling_speed": self.rolling_speed,
            "rolling_omega": self.rolling_omega,
            "t_theory": self.theory["t_star"],
            "x_theory": self.theory["x_star"],
            "v_theory": self.theory["v_star"],
            "omega_theory": self.theory["omega_star"],
            "zone_theory": self.theory["zone"],
        }


class BowlingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Apartado 3 - Complementos")
        self.root.geometry("830x840")
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

        ttk.Label(main, text="Apartado 3 · modelo con complementos", font=("Segoe UI", 13, "bold")).pack(anchor="w", pady=(0, 10))

        frame = ttk.LabelFrame(main, text="Variables", padding=10)
        frame.pack(fill="x", pady=(0, 10))
        fields = [
            ("mass", "Masa (kg)"), ("radius", "Radio (m)"), ("v0", "Velocidad inicial (m/s)"),
            ("omega0", "Omega inicial (rad/s)"), ("beta_real", "Beta real"), ("mu_front", "Mu zona 1"),
            ("mu_back", "Mu zona 2"), ("oil_length", "Longitud zona 1 (m)"), ("mu_rolling", "Roz. rodadura"),
            ("lane_length", "Longitud pista (m)"), ("launch_height", "Altura salida (m)"),
            ("time_scale", "Escala temporal"), ("mu_ideal", "Mu ideal de referencia"),
        ]
        values = self.defaults().__dict__
        for i, (key, label) in enumerate(fields):
            row = i // 2
            col = (i % 2) * 2
            ttk.Label(frame, text=label).grid(row=row, column=col, sticky="w", pady=4)
            var = tk.StringVar(value=str(values[key]))
            ttk.Entry(frame, textvariable=var, width=16).grid(row=row, column=col + 1, sticky="w", pady=4, padx=(8, 16))
            self.vars[key] = var

        buttons = ttk.Frame(main)
        buttons.pack(fill="x", pady=(0, 10))
        ttk.Button(buttons, text="Aplicar", command=self.apply_parameters).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Lanzar", command=self.launch).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Reset", command=self.reset).pack(side="left", padx=(0, 8))
        ttk.Button(buttons, text="Valores por defecto", command=self.load_defaults).pack(side="left")

        theory_frame = ttk.LabelFrame(main, text="Referencia teorica", padding=10)
        theory_frame.pack(fill="x", pady=(0, 10))
        for i, (key, label) in enumerate([
            ("t_star", "Tiempo teorico t* (s)"),
            ("x_star", "Distancia teorica x* (m)"),
            ("v_star", "Velocidad teorica v* (m/s)"),
            ("omega_star", "Omega teorica (rad/s)"),
            ("zone", "Zona teorica de transicion"),
        ]):
            ttk.Label(theory_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(theory_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.theory_labels[key] = lbl

        sim_frame = ttk.LabelFrame(main, text="Simulacion", padding=10)
        sim_frame.pack(fill="x")
        for i, (key, label) in enumerate([
            ("regime", "Estado"), ("zone", "Zona"), ("mu_now", "Mu actual"), ("t", "Tiempo (s)"),
            ("x", "Posicion x (m)"), ("vx", "Velocidad lineal (m/s)"), ("omega", "Velocidad angular (rad/s)"),
            ("wR", "omega·R (m/s)"), ("slip", "Slip v - Rω (m/s)"),
            ("rolling_time", "Transicion a rodadura (s)"),
            ("rolling_speed", "Velocidad en transicion (m/s)"),
            ("delta_t", "Diferencia t real - teorica (s)"),
            ("delta_x", "Diferencia x real - teorica (m)"),
            ("delta_v", "Diferencia v real - teorica (m/s)"),
        ]):
            ttk.Label(sim_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(sim_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.sim_labels[key] = lbl

        ttk.Label(
            main,
            text="Zona 1 con menos rozamiento, zona 2 con mas rozamiento, giro inicial e inercia real.",
        ).pack(anchor="w", pady=(12, 0))

        self.load_defaults()

    def parse_params(self):
        try:
            params = Parameters(
                mass=float(self.vars["mass"].get()),
                radius=float(self.vars["radius"].get()),
                v0=float(self.vars["v0"].get()),
                omega0=float(self.vars["omega0"].get()),
                beta_real=float(self.vars["beta_real"].get()),
                mu_front=float(self.vars["mu_front"].get()),
                mu_back=float(self.vars["mu_back"].get()),
                oil_length=float(self.vars["oil_length"].get()),
                mu_rolling=float(self.vars["mu_rolling"].get()),
                lane_length=float(self.vars["lane_length"].get()),
                launch_height=float(self.vars["launch_height"].get()),
                time_scale=float(self.vars["time_scale"].get()),
                mu_ideal=float(self.vars["mu_ideal"].get()),
            )
        except ValueError:
            raise ValueError("Todos los valores deben ser numericos.")
        if (
            params.mass <= 0 or params.radius <= 0 or params.beta_real <= 0 or
            params.mu_front < 0 or params.mu_back < 0 or params.oil_length <= 0 or
            params.lane_length <= 0 or params.time_scale <= 0 or params.mu_ideal <= 0 or
            params.oil_length >= params.lane_length
        ):
            raise ValueError("Revisa los valores de entrada.")
        return params

    def update_theory(self, theory):
        self.theory_labels["t_star"].config(text="∞" if theory["t_star"] == float("inf") else f"{theory['t_star']:.4f}")
        self.theory_labels["x_star"].config(text="∞" if theory["x_star"] == float("inf") else f"{theory['x_star']:.4f}")
        self.theory_labels["v_star"].config(text=f"{theory['v_star']:.4f}")
        self.theory_labels["omega_star"].config(text=f"{theory['omega_star']:.4f}")
        self.theory_labels["zone"].config(text=theory["zone"])

    def load_defaults(self):
        params = self.defaults()
        for key, value in params.__dict__.items():
            self.vars[key].set(str(value))
        self.update_theory(theory_piecewise(params))

    def apply_parameters(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.sim.params = params
        self.sim.theory = theory_piecewise(params)
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
        self.sim_labels["zone"].config(text=data["zone"])
        self.sim_labels["mu_now"].config(text=f"{data['mu_now']:.4f}")
        self.sim_labels["t"].config(text=f"{data['t']:.4f}")
        self.sim_labels["x"].config(text=f"{data['x']:.4f}")
        self.sim_labels["vx"].config(text=f"{data['vx']:.4f}")
        self.sim_labels["omega"].config(text=f"{data['omega']:.4f}")
        self.sim_labels["wR"].config(text=f"{data['wR']:.4f}")
        self.sim_labels["slip"].config(text=f"{data['slip']:.6f}")
        self.sim_labels["rolling_time"].config(text="-" if data["rolling_time"] is None else f"{data['rolling_time']:.4f}")
        self.sim_labels["rolling_speed"].config(text="-" if data["rolling_speed"] is None else f"{data['rolling_speed']:.4f}")
        if data["rolling_time"] is not None:
            self.sim_labels["delta_t"].config(text=f"{data['rolling_time'] - data['t_theory']:+.4f}")
            self.sim_labels["delta_x"].config(text=f"{data['x'] - data['x_theory']:+.4f}")
            self.sim_labels["delta_v"].config(text=f"{data['rolling_speed'] - data['v_theory']:+.4f}")
        else:
            self.sim_labels["delta_t"].config(text="-")
            self.sim_labels["delta_x"].config(text="-")
            self.sim_labels["delta_v"].config(text="-")

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
