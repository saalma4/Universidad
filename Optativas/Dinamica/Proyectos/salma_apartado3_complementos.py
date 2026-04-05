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
    v0: float = 8.0
    omega0: float = 31.42
    beta_real: float = 0.34
    mu_front: float = 0.08
    mu_back: float = 0.16
    oil_length: float = 12.19
    mu_rolling: float = 0.01
    lane_length: float = 18.29
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
    if abs(s0) < 1e-12:
        return {"t_star": 0.0, "v_star": v0, "omega_star": v0 / radius}
    t_star = beta * abs(s0) / ((1.0 + beta) * mu * G)
    sign = 1.0 if s0 > 0 else -1.0
    v_star = v0 - sign * mu * G * t_star
    omega_star = v_star / radius
    return {"t_star": t_star, "v_star": v_star, "omega_star": omega_star}


class BowlingSimulation(threading.Thread):
    def __init__(self, params: Parameters, ui_callback):
        super().__init__(daemon=True)
        self.params = params
        self.ui_callback = ui_callback
        self._commands = queue.Queue()
        self._stop_event = threading.Event()
        self.client = None
        self.ball_id = None
        self.front_id = None
        self.back_id = None
        self.running = False
        self.ball_launched = False
        self.reached_rolling = False
        self.sim_time = 0.0
        self.last_ui_send_time = 0.0
        self.rolling_time = None
        self.rolling_speed = None
        self.ideal = None

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
        self.running = False
        self.ball_launched = False
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        self.ideal = theory_general(self.params.v0, 0.0, self.params.radius, self.params.mu_ideal, self.params.beta_ideal)

        p.resetSimulation(physicsClientId=self.client)
        p.setGravity(0, 0, -G, physicsClientId=self.client)
        p.setTimeStep(SIM_DT, physicsClientId=self.client)
        p.setPhysicsEngineParameter(fixedTimeStep=SIM_DT, numSolverIterations=300, physicsClientId=self.client)
        p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0, physicsClientId=self.client)

        front_half = self.params.oil_length / 2.0
        back_len = max(self.params.lane_length - self.params.oil_length, 0.5)
        back_half = back_len / 2.0

        shape_front = p.createCollisionShape(p.GEOM_BOX, halfExtents=[front_half, 0.6, 0.02], physicsClientId=self.client)
        vis_front = p.createVisualShape(p.GEOM_BOX, halfExtents=[front_half, 0.6, 0.02], rgbaColor=[0.95, 0.85, 0.55, 1], physicsClientId=self.client)
        self.front_id = p.createMultiBody(baseMass=0, baseCollisionShapeIndex=shape_front, baseVisualShapeIndex=vis_front,
                                          basePosition=[front_half, 0, -0.02], physicsClientId=self.client)
        p.changeDynamics(self.front_id, -1, lateralFriction=self.params.mu_front, rollingFriction=self.params.mu_rolling,
                         spinningFriction=0.0, restitution=0.0, physicsClientId=self.client)

        shape_back = p.createCollisionShape(p.GEOM_BOX, halfExtents=[back_half, 0.6, 0.02], physicsClientId=self.client)
        vis_back = p.createVisualShape(p.GEOM_BOX, halfExtents=[back_half, 0.6, 0.02], rgbaColor=[0.86, 0.86, 0.86, 1], physicsClientId=self.client)
        self.back_id = p.createMultiBody(baseMass=0, baseCollisionShapeIndex=shape_back, baseVisualShapeIndex=vis_back,
                                         basePosition=[self.params.oil_length + back_half, 0, -0.02], physicsClientId=self.client)
        p.changeDynamics(self.back_id, -1, lateralFriction=self.params.mu_back, rollingFriction=self.params.mu_rolling,
                         spinningFriction=0.0, restitution=0.0, physicsClientId=self.client)

        cs = p.createCollisionShape(p.GEOM_SPHERE, radius=self.params.radius, physicsClientId=self.client)
        vs = p.createVisualShape(p.GEOM_SPHERE, radius=self.params.radius, rgbaColor=[0.1, 0.1, 0.12, 1], physicsClientId=self.client)
        self.ball_id = p.createMultiBody(baseMass=self.params.mass, baseCollisionShapeIndex=cs, baseVisualShapeIndex=vs,
                                         basePosition=[0.0, 0.0, self.params.launch_height], physicsClientId=self.client)
        p.changeDynamics(self.ball_id, -1, lateralFriction=self.params.mu_front, rollingFriction=self.params.mu_rolling,
                         spinningFriction=0.0, localInertiaDiagonal=[self.params.inertia_real] * 3,
                         linearDamping=0.0, angularDamping=0.0, restitution=0.0,
                         physicsClientId=self.client)

        p.resetDebugVisualizerCamera(cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
                                     cameraTargetPosition=[2.5, 0.0, 0.0], physicsClientId=self.client)
        self.send_ui("reset_done", self.ideal)

    def launch_ball(self):
        self.sim_time = 0.0
        self.running = True
        self.ball_launched = True
        self.reached_rolling = False
        self.rolling_time = None
        self.rolling_speed = None
        p.resetBasePositionAndOrientation(self.ball_id, [0.0, 0.0, self.params.launch_height], [0, 0, 0, 1], physicsClientId=self.client)
        p.resetBaseVelocity(self.ball_id, linearVelocity=[self.params.v0, 0.0, 0.0], angularVelocity=[0.0, self.params.omega0, 0.0], physicsClientId=self.client)
        self.send_ui("launched", self.ideal)

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

        now = time.perf_counter()
        if now - self.last_ui_send_time >= 1.0 / 30.0:
            data = {
                "t": self.sim_time,
                "x": pos[0],
                "vx": vx,
                "omega": omega,
                "slip": slip,
                "regime": regime,
                "zone": zone,
                "mu_now": mu_now,
                "rolling_time": self.rolling_time,
                "rolling_speed": self.rolling_speed,
                "t_ideal": self.ideal["t_star"],
                "v_ideal": self.ideal["v_star"],
            }
            self.send_ui("telemetry", data)
            self.last_ui_send_time = now

        target_x = max(2.0, pos[0] + 1.5)
        p.resetDebugVisualizerCamera(cameraDistance=4.0, cameraYaw=0, cameraPitch=-18,
                                     cameraTargetPosition=[target_x, 0.0, 0.0], physicsClientId=self.client)


class BowlingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Apartado 3 - Complementos")
        self.root.geometry("800x780")
        self.ui_queue = queue.Queue()
        self.vars = {}
        self.ideal_labels = {}
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

        ideal_frame = ttk.LabelFrame(main, text="Referencia ideal", padding=10)
        ideal_frame.pack(fill="x", pady=(0, 10))
        for i, (key, label) in enumerate([
            ("t_star", "Tiempo ideal (s)"),
            ("v_star", "Velocidad ideal (m/s)"),
            ("omega_star", "Omega ideal (rad/s)"),
        ]):
            ttk.Label(ideal_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(ideal_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.ideal_labels[key] = lbl

        sim_frame = ttk.LabelFrame(main, text="Simulacion", padding=10)
        sim_frame.pack(fill="x")
        for i, (key, label) in enumerate([
            ("regime", "Estado"), ("zone", "Zona"), ("mu_now", "Mu actual"), ("t", "Tiempo (s)"),
            ("x", "Posicion x (m)"), ("vx", "Velocidad lineal (m/s)"), ("omega", "Velocidad angular (rad/s)"),
            ("slip", "Slip v - Rω (m/s)"), ("rolling_time", "Transicion a rodadura (s)"),
            ("rolling_speed", "Velocidad en transicion (m/s)"), ("delta_t", "Diferencia t real - ideal (s)"),
            ("delta_v", "Diferencia v real - ideal (m/s)"),
        ]):
            ttk.Label(sim_frame, text=label).grid(row=i, column=0, sticky="w", pady=3)
            lbl = ttk.Label(sim_frame, text="-")
            lbl.grid(row=i, column=1, sticky="w", padx=(10, 0))
            self.sim_labels[key] = lbl

        ttk.Label(main, text="En este apartado se anaden: inercia distinta, rozamiento por rodadura, pista por zonas y giro inicial.").pack(anchor="w", pady=(12, 0))
        self.load_defaults()

    def parse_params(self):
        try:
            params = Parameters(
                mass=float(self.vars["mass"].get()), radius=float(self.vars["radius"].get()),
                v0=float(self.vars["v0"].get()), omega0=float(self.vars["omega0"].get()),
                beta_real=float(self.vars["beta_real"].get()), mu_front=float(self.vars["mu_front"].get()),
                mu_back=float(self.vars["mu_back"].get()), oil_length=float(self.vars["oil_length"].get()),
                mu_rolling=float(self.vars["mu_rolling"].get()), lane_length=float(self.vars["lane_length"].get()),
                launch_height=float(self.vars["launch_height"].get()), time_scale=float(self.vars["time_scale"].get()),
                mu_ideal=float(self.vars["mu_ideal"].get()),
            )
        except ValueError:
            raise ValueError("Todos los valores deben ser numericos.")
        if params.mass <= 0 or params.radius <= 0 or params.beta_real <= 0 or params.mu_front < 0 or params.mu_back < 0:
            raise ValueError("Revisa los valores de entrada.")
        return params

    def update_ideal(self, ideal):
        for k, lbl in self.ideal_labels.items():
            lbl.config(text=f"{ideal[k]:.4f}")

    def load_defaults(self):
        params = self.defaults()
        for key, value in params.__dict__.items():
            self.vars[key].set(str(value))
        self.update_ideal(theory_general(params.v0, 0.0, params.radius, params.mu_ideal, params.beta_ideal))

    def apply_parameters(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.update_ideal(theory_general(params.v0, 0.0, params.radius, params.mu_ideal, params.beta_ideal))
        self.sim.post_command("update_params", params)

    def launch(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.update_ideal(theory_general(params.v0, 0.0, params.radius, params.mu_ideal, params.beta_ideal))
        self.sim.post_command("update_params", params)
        self.sim.post_command("launch")

    def reset(self):
        try:
            params = self.parse_params()
        except ValueError as e:
            messagebox.showerror("Error", str(e))
            return
        self.update_ideal(theory_general(params.v0, 0.0, params.radius, params.mu_ideal, params.beta_ideal))
        self.sim.post_command("reset", params)

    def start_simulation(self):
        self.sim = BowlingSimulation(self.defaults(), self.ui_queue.put)
        self.sim.start()

    def process_ui_queue(self):
        try:
            while True:
                kind, data = self.ui_queue.get_nowait()
                if kind == "reset_done":
                    self.update_ideal(data)
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
        self.sim_labels["zone"].config(text=data["zone"])
        self.sim_labels["mu_now"].config(text=f"{data['mu_now']:.4f}")
        self.sim_labels["t"].config(text=f"{data['t']:.4f}")
        self.sim_labels["x"].config(text=f"{data['x']:.4f}")
        self.sim_labels["vx"].config(text=f"{data['vx']:.4f}")
        self.sim_labels["omega"].config(text=f"{data['omega']:.4f}")
        self.sim_labels["slip"].config(text=f"{data['slip']:.6f}")
        self.sim_labels["rolling_time"].config(text="-" if data['rolling_time'] is None else f"{data['rolling_time']:.4f}")
        self.sim_labels["rolling_speed"].config(text="-" if data['rolling_speed'] is None else f"{data['rolling_speed']:.4f}")
        if data['rolling_time'] is not None:
            self.sim_labels["delta_t"].config(text=f"{data['rolling_time'] - data['t_ideal']:+.4f}")
            self.sim_labels["delta_v"].config(text=f"{data['rolling_speed'] - data['v_ideal']:+.4f}")
        else:
            self.sim_labels["delta_t"].config(text="-")
            self.sim_labels["delta_v"].config(text="-")

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
