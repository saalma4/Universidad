import os
import math
import pygame
import pymunk
from pymunk import Vec2d

BASE_DIR = os.path.dirname(os.path.abspath(__file__))


def ruta_recurso(nombre):
    """Permite cargar imágenes tanto desde la carpeta del script como desde el cwd."""
    ruta = os.path.join(BASE_DIR, nombre)
    return ruta if os.path.exists(ruta) else nombre


################################# SIMULACIÓN GENÉRICA ##############################################
class Tsim:
    def __init__(self, width=1000, height=600, suelo=600, PX_M=1, gravedad=(0, -9.81), fondo=None):
        self.width = width
        self.height = height
        self.PX_M = PX_M
        self.M_PX = 1.0 / PX_M
        self.suelo = suelo
        

        pygame.init()
        self.screen = pygame.display.set_mode((self.width, self.height))
        self.clock = pygame.time.Clock()

        self.fondo = self.pone_fondo(fondo) if fondo is not None else None

        self.space = pymunk.Space()
        # En nuestra interfaz física: y positiva hacia arriba.
        # En Pygame/Pymunk: y positiva hacia abajo, por eso invertimos la componente y.
        self.space.gravity = Vec2d(gravedad[0], -gravedad[1]) * PX_M
        self.space.iterations = 35
        self.space.collision_slop = 0.2
        self.space.collision_bias = 0.6

        self._eventos_teclado = {}
        self.running = True

    def pone_fondo(self, imagen):
        try:
            fondo = pygame.image.load(ruta_recurso(imagen)).convert()
            fondo = pygame.transform.smoothscale(fondo, (self.width, self.height))
        except Exception:
            fondo = None
        self.fondo = fondo
        return fondo

    def draw(self):
        if self.fondo:
            self.screen.blit(self.fondo, (0, 0))
        else:
            self.screen.fill((240, 240, 240))

    def add_evento_tecla(self, tecla, funcion, activo=True):
        self._eventos_teclado[tecla] = {"func": funcion, "activo": activo}

    def set_estado_evento(self, tecla, estado):
        if tecla in self._eventos_teclado:
            self._eventos_teclado[tecla]["activo"] = estado

    def actualizar_eventos(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
                return False

            if event.type == pygame.KEYDOWN:
                if event.key in self._eventos_teclado:
                    evento = self._eventos_teclado[event.key]
                    if evento["activo"]:
                        evento["func"]()
        return True


###############################################################################################
# Objeto genérico: concentra las conversiones metro <-> píxel y m/s <-> px/s.
class Tobjeto:
    def __init__(self, sim):
        self.sim = sim

    def _m_a_px(self, pos_m):
        x_px = pos_m[0] * self.sim.PX_M
        y_px = self.sim.suelo - (pos_m[1] * self.sim.PX_M)
        return Vec2d(x_px, y_px)

    def _px_a_m(self, pos_px):
        x_m = pos_px[0] / self.sim.PX_M
        y_m = (self.sim.suelo - pos_px[1]) / self.sim.PX_M
        return Vec2d(x_m, y_m)

    def _v_m_a_px(self, vel_m):
        return Vec2d(vel_m[0] * self.sim.PX_M, -vel_m[1] * self.sim.PX_M)

    def _v_px_a_m(self, vel_px):
        v = Vec2d(vel_px[0], vel_px[1]) / self.sim.PX_M
        return Vec2d(v.x, -v.y)

    def _f_N_a_pm(self, fuerza_N):
        """Convierte Newtons físicos (y arriba positivo) a fuerza Pymunk (y abajo positivo)."""
        return Vec2d(fuerza_N[0] * self.sim.PX_M, -fuerza_N[1] * self.sim.PX_M)

    @property
    def posicion(self):
        return self._px_a_m(self.body.position)

    @posicion.setter
    def posicion(self, pos_m):
        self.body.position = self._m_a_px(pos_m)

    @property
    def velocidad(self):
        return self._v_px_a_m(self.body.velocity)

    @velocidad.setter
    def velocidad(self, vel_m):
        self.body.velocity = self._v_m_a_px(vel_m)

    def aplicar_impulso(self, imp_m):
        imp_px = Vec2d(imp_m[0], -imp_m[1]) * self.sim.PX_M
        self.body.apply_impulse_at_local_point(imp_px)


class Tsuelo(Tobjeto):
    def __init__(self, sim, punto_a_m=None, punto_b_m=None, color=(0, 0, 0)):
        super().__init__(sim)
        self.color = color
        self.body = self.sim.space.static_body

        self.p1 = Vec2d(0, self.sim.suelo) if punto_a_m is None else self._m_a_px(punto_a_m)
        self.p2 = Vec2d(self.sim.width, self.sim.suelo) if punto_b_m is None else self._m_a_px(punto_b_m)

        self.shape = pymunk.Segment(self.body, self.p1, self.p2, 0)
        self.shape.elasticity = 0.8
        self.shape.friction = 0.6
        self.sim.space.add(self.shape)

    @Tobjeto.posicion.setter
    def posicion(self, valor):
        print("Advertencia: No se puede mover el suelo, es un objeto estático.")

    @Tobjeto.velocidad.setter
    def velocidad(self, valor):
        print("Advertencia: No se puede asignar velocidad al suelo.")

    def draw(self):
        pygame.draw.line(self.sim.screen, self.color, self.p1, self.p2, 2)


class Tbalon(Tobjeto):
    def __init__(self, sim, pos_m, masa_kg=0.625, radio_m=0.119, img_path="balon_basket.png"):
        super().__init__(sim)
        self.radio_m = radio_m
        self.radio_px = radio_m * self.sim.PX_M
        self.area_m2 = math.pi * radio_m ** 2

        # Parámetros realistas para balón de baloncesto según el Tema 6.
        self.Cd = 0.50       # esfera rugosa / balón de basket
        self.rho = 1.225     # kg/m^3
        self.k_magnus = 0.60 # similar a voleibol/balón grande; efecto pequeño
        self.Cm_rot = 0.018  # frenado rotacional tipo balón cosido/sintético
        self.usar_aire = True
        self.usar_magnus = True
        self.usar_frenado_rotacional = True
        self.viento_m_s = Vec2d(0, 0)

        moment = pymunk.moment_for_circle(masa_kg, 0, self.radio_px)
        self.body = pymunk.Body(masa_kg, moment)
        self.posicion = pos_m

        self.shape = pymunk.Circle(self.body, self.radio_px)
        self.shape.elasticity = 0.85
        self.shape.friction = 0.5
        self.sim.space.add(self.body, self.shape)

        self.img_base = self._preparar_imagen(img_path)

    def _preparar_imagen(self, path):
        diametro = int(self.radio_px * 2)
        try:
            img = pygame.image.load(ruta_recurso(path)).convert_alpha()
            return pygame.transform.smoothscale(img, (diametro, diametro))
        except Exception:
            surf = pygame.Surface((diametro, diametro), pygame.SRCALPHA)
            pygame.draw.circle(surf, (200, 50, 50), (int(self.radio_px), int(self.radio_px)), int(self.radio_px))
            pygame.draw.line(surf, (255, 255, 255), (int(self.radio_px), int(self.radio_px)), (diametro, int(self.radio_px)), 2)
            return surf

    def configurar_aerodinamica(self, Cd=None, k_magnus=None, Cm_rot=None, viento_m_s=None,
                                usar_aire=None, usar_magnus=None, usar_frenado_rotacional=None):
        if Cd is not None:
            self.Cd = Cd
        if k_magnus is not None:
            self.k_magnus = k_magnus
        if Cm_rot is not None:
            self.Cm_rot = Cm_rot
        if viento_m_s is not None:
            self.viento_m_s = Vec2d(*viento_m_s)
        if usar_aire is not None:
            self.usar_aire = usar_aire
        if usar_magnus is not None:
            self.usar_magnus = usar_magnus
        if usar_frenado_rotacional is not None:
            self.usar_frenado_rotacional = usar_frenado_rotacional

    def _coef_magnus(self, speed):
        if speed <= 1e-9:
            return 0.0
        S = abs(self.radio_m * self.body.angular_velocity) / speed
        return self.k_magnus * S / (2.0 + S)

    def aplicar_aerodinamica(self):
        """Arrastre de Newton + Magnus + frenado rotacional, aplicados a mano en cada substep."""
        v_rel = self.velocidad - self.viento_m_s
        speed = v_rel.length
        if speed < 0.05:
            return

        if self.usar_aire:
            # F_drag = -1/2*rho*Cd*A*|v|*v
            F_drag_N = -0.5 * self.rho * self.Cd * self.area_m2 * speed * v_rel
            self.body.apply_force_at_world_point(self._f_N_a_pm(F_drag_N), self.body.position)

        if self.usar_magnus and abs(self.body.angular_velocity) > 0.01:
            # Normal física a la trayectoria. Con omega negativa (backspin), elevamos el balón.
            normal = Vec2d(-v_rel.y, v_rel.x)
            if normal.length > 0:
                normal = normal.normalized()
                direccion = -1.0 if self.body.angular_velocity > 0 else 1.0
                Cm = self._coef_magnus(speed)
                F_magnus_N = direccion * 0.5 * self.rho * self.area_m2 * Cm * speed ** 2 * normal
                self.body.apply_force_at_world_point(self._f_N_a_pm(F_magnus_N), self.body.position)

        if self.usar_frenado_rotacional and abs(self.body.angular_velocity) > 0.01:
            w = self.body.angular_velocity
            torque_mag = 0.5 * self.rho * (w ** 2) * (self.radio_m ** 5) * self.Cm_rot
            self.body.torque += -math.copysign(torque_mag, w) * (self.sim.PX_M ** 2)

    def draw(self):
        angulo_deg = math.degrees(-self.body.angle)
        img_rotada = pygame.transform.rotate(self.img_base, angulo_deg)
        pos = self.body.position
        rect = img_rotada.get_rect(center=(int(pos.x), int(pos.y)))
        self.sim.screen.blit(img_rotada, rect)

    def lanzar(self, v_ms, angulo_deg, omega=0):
        rad = math.radians(angulo_deg)
        self.velocidad = (v_ms * math.cos(rad), v_ms * math.sin(rad))
        self.body.angular_velocity = omega


class Tred(Tobjeto):
    """Red física inspirada en basquet05: bolitas con PinJoint y muelles transversales."""
    def __init__(self, sim, body_delantero, body_trasero, niveles=4):
        super().__init__(sim)
        self.body = sim.space.static_body
        self.body_delantero = body_delantero
        self.body_trasero = body_trasero
        self.niveles = niveles
        self.radio_bolita = 0.018 * sim.PX_M
        self.masa_bolita = 0.010
        self.cadenas = []
        self.muelles = []
        self.color = (255, 255, 255)
        self._crear_red()

    def _crear_red(self):
        dist_px = 0.10 * self.sim.PX_M
        for anclaje in [self.body_delantero, self.body_trasero]:
            cadena = []
            padre = anclaje
            for i in range(self.niveles):
                momento = pymunk.moment_for_circle(self.masa_bolita, 0, self.radio_bolita)
                hijo = pymunk.Body(self.masa_bolita, momento)
                hijo.position = (padre.position.x, padre.position.y + dist_px)
                shape = pymunk.Circle(hijo, self.radio_bolita)
                shape.elasticity = 0.35
                shape.friction = 0.8
                union = pymunk.PinJoint(padre, hijo, (0, 0), (0, 0))
                self.sim.space.add(hijo, shape, union)
                cadena.append(hijo)
                padre = hijo
            self.cadenas.append(cadena)

        # Muelles horizontales: hacen que la red interactúe y vuelva a cerrarse.
        for i in range(self.niveles):
            ancho = (0.36 - 0.055 * i) * self.sim.PX_M
            muelle = pymunk.DampedSpring(
                self.cadenas[0][i], self.cadenas[1][i],
                (0, 0), (0, 0),
                ancho,
                45.0,
                3.0
            )
            self.sim.space.add(muelle)
            self.muelles.append(muelle)

        # Cruces diagonales para que la red parezca malla y sea más flexible.
        for i in range(self.niveles - 1):
            for a, b in [(self.cadenas[0][i], self.cadenas[1][i + 1]),
                         (self.cadenas[1][i], self.cadenas[0][i + 1])]:
                diagonal = pymunk.DampedSpring(a, b, (0, 0), (0, 0), 0.16 * self.sim.PX_M, 20.0, 2.5)
                self.sim.space.add(diagonal)
                self.muelles.append(diagonal)

    def amortiguar(self):
        # Pequeño damping artificial para que no vibre eternamente.
        for cadena in self.cadenas:
            for b in cadena:
                b.velocity *= 0.96
                b.angular_velocity *= 0.96

    def draw(self):
        bolas_izq, bolas_der = self.cadenas
        for cadena, anclaje in [(bolas_izq, self.body_delantero), (bolas_der, self.body_trasero)]:
            padre_pos = anclaje.position
            for hijo in cadena:
                pygame.draw.line(self.sim.screen, self.color, padre_pos, hijo.position, 1)
                padre_pos = hijo.position

        for i in range(self.niveles):
            pygame.draw.line(self.sim.screen, self.color, bolas_izq[i].position, bolas_der[i].position, 1)
        for i in range(self.niveles - 1):
            pygame.draw.line(self.sim.screen, self.color, bolas_izq[i].position, bolas_der[i + 1].position, 1)
            pygame.draw.line(self.sim.screen, self.color, bolas_der[i].position, bolas_izq[i + 1].position, 1)

        for b in bolas_izq + bolas_der:
            pygame.draw.circle(self.sim.screen, self.color, (int(b.position.x), int(b.position.y)), int(self.radio_bolita))


class Ttablero(Tobjeto):
    def __init__(self, sim, x_tablero_m=7, color=(100, 100, 100)):
        super().__init__(sim)
        self.color = color
        self.espesor = 0.05 * sim.PX_M
        self.alto = 1.05 * sim.PX_M

        self.body = self.sim.space.static_body
        self.pos = self._m_a_px((x_tablero_m, 2.90))
        p0 = Vec2d(self.pos.x, self.pos.y - self.alto)
        p1 = Vec2d(self.pos.x + self.espesor, self.pos.y - self.alto)
        p2 = Vec2d(self.pos.x + self.espesor, self.pos.y)
        p3 = Vec2d(self.pos.x, self.pos.y)
        self.shape = pymunk.Poly(self.body, [p0, p1, p2, p3])
        self.shape.elasticity = 0.60
        self.shape.friction = 0.6
        self.sim.space.add(self.shape)

        _, self.aro_y = self._m_a_px((0, 3.05))
        diametro_aro = 0.45 * sim.PX_M
        self.x_aro_trasero = self.pos.x - (0.15 * sim.PX_M)
        self.x_aro_delantero = self.x_aro_trasero - diametro_aro

        self.aro_part_w = 0.04 * sim.PX_M
        self.aro_part_h = 0.02 * sim.PX_M
        self.x_aro_sop = self.x_aro_trasero + self.aro_part_w

        self.body_trasero = pymunk.Body(body_type=pymunk.Body.STATIC)
        self.body_trasero.position = (self.x_aro_trasero, self.aro_y)
        self.aro_trasero_shape = pymunk.Poly.create_box(self.body_trasero, (self.aro_part_w, self.aro_part_h))

        self.body_delantero = pymunk.Body(body_type=pymunk.Body.STATIC)
        self.body_delantero.position = (self.x_aro_delantero, self.aro_y)
        self.aro_delantero_shape = pymunk.Poly.create_box(self.body_delantero, (self.aro_part_w, self.aro_part_h))

        self.body_sop = pymunk.Body(body_type=pymunk.Body.STATIC)
        self.body_sop.position = (self.x_aro_sop, self.aro_y)
        self.aro_sop_shape = pymunk.Poly.create_box(self.body_sop, (self.aro_part_w * 2, self.aro_part_h))

        # IMPORTANTE: en el archivo original se creaban las shapes del aro, pero no se añadían al espacio.
        for shape in [self.aro_trasero_shape, self.aro_delantero_shape, self.aro_sop_shape]:
            shape.elasticity = 0.45
            shape.friction = 0.6
            self.sim.space.add(shape.body, shape)

        self.red = Tred(sim, self.body_delantero, self.body_trasero)

    def amortiguar_red(self):
        self.red.amortiguar()

    def draw(self):
        pygame.draw.rect(self.sim.screen, self.color, (self.pos.x, self.pos.y - self.alto, self.espesor, self.alto))

        color_sop = (255, 150, 150)
        sopx = 0.10 * self.sim.PX_M
        sopy = 0.40 * self.sim.PX_M
        barrax = 0.05 * self.sim.PX_M

        pygame.draw.rect(self.sim.screen, color_sop, (self.pos.x + self.espesor, self.pos.y - 0.6 * self.alto, sopx, sopy))
        pygame.draw.rect(self.sim.screen, color_sop, (self.pos.x + self.espesor + sopx, 0, barrax, self.pos.y - 0.4 * self.alto))

        self.red.draw()

        color_aro_suave = (255, 150, 150)
        pygame.draw.line(self.sim.screen, color_aro_suave, (int(self.x_aro_delantero), int(self.aro_y)), (int(self.x_aro_trasero), int(self.aro_y)), 3)
        for b in [self.body_trasero, self.body_delantero]:
            pygame.draw.rect(self.sim.screen, (200, 0, 0), (int(b.position.x - self.aro_part_w / 2), int(b.position.y - self.aro_part_h / 2), int(self.aro_part_w), int(self.aro_part_h)))
        pygame.draw.rect(self.sim.screen, (200, 0, 0), (int(self.x_aro_sop - self.aro_part_w), int(self.aro_y - self.aro_part_h / 2), int(self.aro_part_w * 2), int(self.aro_part_h)))


class Tjugador:
    def __init__(self, sim, x_m=2.0, altura_m_reposo=2.0, altura_m_lanzando=2.2):
        self.sim = sim
        self.x_m = x_m
        self.lanzando = False
        self.imgs = {
            False: self._cargar("jugador01.png", altura_m_reposo),
            True: self._cargar("jugador02.png", altura_m_lanzando),
        }

    def _cargar(self, nombre, altura_m):
        try:
            img = pygame.image.load(ruta_recurso(nombre)).convert_alpha()
            ratio = img.get_width() / img.get_height()
            alto_px = int(altura_m * self.sim.PX_M)
            return pygame.transform.smoothscale(img, (int(alto_px * ratio), alto_px))
        except Exception:
            return None

    def set_lanzando(self, estado):
        self.lanzando = estado

    def draw(self):
        img = self.imgs[self.lanzando]
        x_px = int(self.x_m * self.sim.PX_M)
        y_px = int(self.sim.suelo)
        if img:
            rect = img.get_rect(midbottom=(x_px, y_px))
            self.sim.screen.blit(img, rect)
        else:
            pygame.draw.rect(self.sim.screen, (40, 80, 200), (x_px - 20, y_px - 180, 40, 180))
            pygame.draw.circle(self.sim.screen, (230, 180, 140), (x_px, y_px - 205), 20)


########## CLASE ESPECÍFICA DE BALONCESTO ######################################
class Tbasket(Tsim):
    def __init__(self, x_tablero_m=7, pos_balon_m=(1, 2), **kwargs):
        super().__init__(**kwargs)
        self.pos_inicio_balon = pos_balon_m

        self.v_lanzamiento = 9.0
        self.ang_lanzamiento = 55.0
        self.w_lanzamiento = -15.0

        self.balon = Tbalon(self, self.pos_inicio_balon)
        self.suelo_fisico = Tsuelo(self)
        self.tablero = Ttablero(self, x_tablero_m)
        self.jugador = Tjugador(self, x_m=pos_balon_m[0])


        # Diccionario de objetos: draw() recorre automáticamente todo lo dibujable.
        self.objetos = {
            "jugador": self.jugador,
            "suelo": self.suelo_fisico,
            "tablero": self.tablero,
            "balon": self.balon,
        }

        self.add_evento_tecla(pygame.K_SPACE, self.lanzar_triple)
        self.add_evento_tecla(pygame.K_ESCAPE, self.resetear_posicion)

    def lanzar_triple(self):
        print(f"Lanzando a {self.v_lanzamiento} m/s con {self.ang_lanzamiento}º")
        self.balon.lanzar(self.v_lanzamiento, self.ang_lanzamiento, self.w_lanzamiento)
        self.jugador.set_lanzando(True)
        self.set_estado_evento(pygame.K_SPACE, False)

    def configurar_tiro(self, v=None, ang=None, w=None):
        if v is not None:
            self.v_lanzamiento = v
        if ang is not None:
            self.ang_lanzamiento = ang
        if w is not None:
            self.w_lanzamiento = w

    def resetear_posicion(self):
        self.balon.posicion = self.pos_inicio_balon
        self.balon.body.velocity = (0, 0)
        self.balon.body.force = (0, 0)
        self.balon.body.angular_velocity = 0
        self.balon.body.torque = 0
        self.jugador.set_lanzando(False)
        self.set_estado_evento(pygame.K_SPACE, True)

    def update(self, dt):
        self.balon.aplicar_aerodinamica()
        self.tablero.amortiguar_red()

    def draw(self):
        # Reescritura correcta del método de Tsim: primero se pinta fondo con super().draw().
        super().draw()
        for objeto in self.objetos.values():
            objeto.draw()

    # Alias por compatibilidad con el archivo original.
    def dibujar_todo(self):
        self.draw()


if __name__ == "__main__":
    bk = Tbasket(
        x_tablero_m=7,
        pos_balon_m=(2, 2),
        PX_M=120,
        width=1000,
        height=600,
        suelo=560,
        gravedad=(0, -9.81),
        fondo="grada_baloncesto03.jpg",
    )

    # Prueba: tiro tipo triple. SPACE lanza, ESC resetea.
    bk.configurar_tiro(8.8, 52, -18)
    bk.balon.configurar_aerodinamica(Cd=0.50, k_magnus=0.60, Cm_rot=0.018)

    FPS = 60
    substeps = 30
    dt = 1.0 / FPS / substeps

    while bk.actualizar_eventos():
        for _ in range(substeps):
            bk.update(dt)
            bk.space.step(dt)

        bk.draw()
        pygame.display.flip()
        bk.clock.tick(FPS)

    pygame.quit()
