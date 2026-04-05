import math
import queue
import threading
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
    mu: float = 0.18
    v0: float = 8.0
    lane_length: float = 18.29
    launch_height: float = 0.111
    time_scale: float = 1.0

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


class BowlingSimulation(threading.Thread):
    def __init__(self, params: Parameters, ui_callback):
        super().__init__(daemon=True)
        self.params = params
        self.ui_callback = ui_callback
        self._commands = queue.Queue()
        self._stop_event = threading.Event()

        self.client = None
        self.ball_id = None
        self.ground_id = None
        self.sim_time = 0.0
        self.last_ui_send_time = 0.0
        self.ball_launched = False
        self.running = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = None

    def post_command(self, cmd, payload=None):
        self._commands.put((cmd, payload))

    def stop(self):
        self._stop_event.set()
        self.post_command("quit")

    def send_ui(self, kind, data):
        self.ui_callback((kind, data))

    def reset_world(self):
        self.sim_time = 0.0
        self.last_ui_send_time = 0.0
        self.ball_launched = False
        self.running = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = compute_theory(self.params)

        p.resetSimulation(physicsClientId=self.client)
        p.setGravity(0, 0, -G, physicsClientId=self.client)
        p.setTimeStep(SIM_DT, physicsClientId=self.client)
        p.setPhysicsEngineParameter(fixedTimeStep=SIM_DT, numSolverIterations=300, physicsClientId=self.client)
        p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0, physicsClientId=self.client)

        half_len = self.params.lane_length / 2.0
        shape = p.createCollisionShape(p.GEOM_BOX, halfExtents=[half_len, 0.6, 0.02], physicsClientId=self.client)
        visual = p.createVisualShape(p.GEOM_BOX, halfExtents=[half_len, 0.6, 0.02], rgbaColor=[0.82, 0.72, 0.52, 1], physicsClientId=self.client)
        self.ground_id = p.createMultiBody(baseMass=0, baseCollisionShapeIndex=shape, baseVisualShapeIndex=visual,
                                           basePosition=[half_len, 0, -0.02], physicsClientId=self.client)
        p.changeDynamics(self.ground_id, -1, lateralFriction=self.params.mu, rollingFriction=0.0,
                         spinningFriction=0.0, restitution=0.0, physicsClientId=self.client)

        cs = p.createCollisionShape(p.GEOM_SPHERE, radius=self.params.radius, physicsClientId=self.client)
        vs = p.createVisualShape(p.GEOM_SPHERE, radius=self.params.radius, rgbaColor=[0.05, 0.05, 0.08, 1], physicsClientId=self.client)
        self.ball_id = p.createMultiBody(baseMass=self.params.mass, baseCollisionShapeIndex=cs, baseVisualShapeIndex=vs,
                                         basePosition=[0.0, 0.0, self.params.launch_height], physicsClientId=self.client)
        p.changeDynamics(self.ball_id, -1, lateralFriction=self.params.mu, rollingFriction=0.0,
                         spinningFriction=0.0, localInertiaDiagonal=[self.params.inertia] * 3,
                         linearDamping=0.0, angularDamping=0.0, restitution=0.0,
                         physicsClientId=self.client)

        p.resetDebugVisualizerCamera(cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
                                     cameraTargetPosition=[2.5, 0.0, 0.0], physicsClientId=self.client)
        self.send_ui("reset_done", self.theory)

    def launch_ball(self):
        self.sim_time = 0.0
        self.ball_launched = True
        self.running = True
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.rolling_omega = None
        self.theory = compute_theory(self.params)
        p.resetBasePositionAndOrientation(self.ball_id, [0.0, 0.0, self.params.launch_height], [0, 0, 0, 1], physicsClientId=self.client)
        p.resetBaseVelocity(self.ball_id, linearVelocity=[self.params.v0, 0.0, 0.0], angularVelocity=[0.0, 0.0, 0.0], physicsClientId=self.client)
        self.send_ui("launched", self.theory)

    def _handle_commands(self):
        while True:
            try:
                cmd, payload = self._commands.get_nowait()
            except queue.Empty:
                break
            if cmd == "update_params":
                self.params = payload
            elif cmd == "reset":
                self.params = payload
                self.reset_world()
            elif cmd == "launch":
                self.launch_ball()
            elif cmd == "quit":
                return False
        return True

    def run(self):
        self.client = p.connect(p.GUI)
        self.reset_world()
        while not self._stop_event.is_set():
            if not self._handle_commands():
                break
            if self.ball_id is not None:
                self.step_simulation()
            p.stepSimulation(physicsClientId=self.client)
            if self.running and self.ball_launched:
                self.sim_time += SIM_DT
            time.sleep(SIM_DT / max(self.params.time_scale, 1e-6))
        if self.client is not None:
            p.disconnect(self.client)

    def step_simulation(self):
        pos, _ = p.getBasePositionAndOrientation(self.ball_id, physicsClientId=self.client)
        lin_vel, ang_vel = p.getBaseVelocity(self.ball_id, physicsClientId=self.client)
        vx = lin_vel[0]
        omega = ang_vel[1]
        slip = vx - self.params.radius * omega
        speed_ref = max(abs(vx), abs(self.params.radius * omega), 1e-6)
        pure = abs(slip) / speed_ref <= PURE_ROLLING_REL_TOL

        if self.ball_launched and not self.reached_rolling and pure:
            self.reached_rolling = True
            self.rolling_time = self.sim_time
            self.rolling_speed = vx
            self.rolling_omega = omega

        regime = "En espera"
        if self.ball_launched:
            if abs(vx) <= STOP_SPEED and abs(omega) <= STOP_SPEED / max(self.params.radius, 1e-9):
                regime = "Parada"
            elif pure:
                regime = "Rodadura pura"
            else:
                regime = "Deslizamiento"

        now = time.perf_counter()
        if now - self.last_ui_send_time >= 1.0 / 30.0:
            data = {
                "t": self.sim_time,
                "x": pos[0],
                "vx": vx,
                "omega": omega,
                "slip": slip,
                "regime": regime,
                "rolling_time": self.rolling_time,
                "rolling_speed": self.rolling_speed,
                "rolling_omega": self.rolling_omega,
                "t_theory": self.theory["t_star"],
                "v_theory": self.theory["v_star"],
            }
            self.send_ui("telemetry", data)
            self.last_ui_send_time = now

        target_x = max(2.0, pos[0] + 1.5)
        p.resetDebugVisualizerCamera(cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
                                     cameraTargetPosition=[target_x, 0.0, 0.0], physicsClientId=self.client)


class BowlingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Apartado 2 - Simulacion base")
        self.root.geometry("760x720")
        self.ui_queue = queue.Queue()
        self.vars = {}
        self.theory_labels = {}
        self.sim_labels = {}
        self.sim = None
        self.build_ui()
        self.start_simulation()
        self.root.after(30, self.process_ui_queue)
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

        ttk.Label(main, text="En este apartado la bola sale sin giro inicial y se compara con la teoria ideal.").pack(anchor="w", pady=(12, 0))

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
        if params.mass <= 0 or params.radius <= 0 or params.mu <= 0 or params.v0 < 0 or params.lane_length <= 0:
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
        self.update_theory(compute_theory(params))
        if self.sim is not None:
            self.sim.post_command("update_params", params)

    def launch(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.update_theory(compute_theory(params))
        self.sim.post_command("update_params", params)
        self.sim.post_command("launch")

    def reset(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.update_theory(compute_theory(params))
        self.sim.post_command("reset", params)

    def start_simulation(self):
        params = self.defaults()
        self.sim = BowlingSimulation(params, self.ui_queue.put)
        self.sim.start()

    def process_ui_queue(self):
        try:
            while True:
                kind, data = self.ui_queue.get_nowait()
                if kind == "reset_done":
                    self.update_theory(data)
                    for lbl in self.sim_labels.values():
                        lbl.config(text="-")
                    self.sim_labels["regime"].config(text="En espera")
                elif kind == "telemetry":
                    self.refresh_telemetry(data)
        except queue.Empty:
            pass
        self.root.after(30, self.process_ui_queue)

    def refresh_telemetry(self, data):
        self.sim_labels["regime"].config(text=data["regime"])
        self.sim_labels["t"].config(text=f"{data['t']:.4f}")
        self.sim_labels["x"].config(text=f"{data['x']:.4f}")
        self.sim_labels["vx"].config(text=f"{data['vx']:.4f}")
        self.sim_labels["omega"].config(text=f"{data['omega']:.4f}")
        self.sim_labels["slip"].config(text=f"{data['slip']:.6f}")
        self.sim_labels["rolling_time"].config(text="-" if data['rolling_time'] is None else f"{data['rolling_time']:.4f}")
        self.sim_labels["rolling_speed"].config(text="-" if data['rolling_speed'] is None else f"{data['rolling_speed']:.4f}")
        if data['rolling_time'] is not None:
            err_t = 100.0 * abs(data['rolling_time'] - data['t_theory']) / max(data['t_theory'], 1e-9)
            err_v = 100.0 * abs(data['rolling_speed'] - data['v_theory']) / max(abs(data['v_theory']), 1e-9)
            self.sim_labels["error_t"].config(text=f"{err_t:.4f}")
            self.sim_labels["error_v"].config(text=f"{err_v:.4f}")
        else:
            self.sim_labels["error_t"].config(text="-")
            self.sim_labels["error_v"].config(text="-")

    def on_close(self):
        if self.sim is not None:
            self.sim.stop()
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
