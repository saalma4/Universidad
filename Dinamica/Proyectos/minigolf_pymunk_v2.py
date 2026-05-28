from __future__ import annotations

from dataclasses import dataclass
import math
import sys
from typing import Iterable

import pygame
import pymunk
from pymunk import Vec2d


# =============================================================================
# Configuracion general
# =============================================================================

FPS = 60
SUBSTEPS = 4
DT = 1.0 / FPS

PX_M = 360.0
COURSE_W_M = 3.60
COURSE_H_M = 2.15
PANEL_H_PX = 96
SCREEN_W = int(COURSE_W_M * PX_M)
SCREEN_H = int(COURSE_H_M * PX_M) + PANEL_H_PX

G = 9.81
BALL_MASS = 0.04593
BALL_RADIUS = 0.02134
HOLE_RADIUS = 0.055

MAX_IMPULSE = 0.18
MAX_DRAG_DISTANCE_M = 0.85
STOP_SPEED = 0.035
HOLE_CAPTURE_SPEED = 0.85
# La bola no entra si solo roza el borde del agujero: se exige que el centro
# quede dentro de una zona de captura interior y que la velocidad sea baja.
# Este criterio evita embocar golpes que pasan demasiado rapido por encima.
HOLE_CAPTURE_RADIUS_FACTOR = 0.72

# La velocidad angular no se usa para decidir la trayectoria. En una vista cenital
# Pymunk solo ofrece un giro escalar alrededor del eje perpendicular a la pantalla;
# por eso se usa como representacion visual de la rodadura de la bola.
ROLL_SPIN_SMOOTHING = 0.08

WATER_PENALTY = 1

BALL_ELASTICITY = 0.62
WALL_ELASTICITY = 0.72
OBSTACLE_ELASTICITY = 0.55
BALL_FRICTION = 0.60
WALL_FRICTION = 0.80

BACKGROUND = (28, 94, 47)
PANEL_COLOR = (24, 27, 31)
TEXT_COLOR = (235, 235, 235)
AIM_COLOR = (240, 240, 240)

#Propiedades de una zona de terreno
@dataclass(frozen=True)
class SurfaceType:
    name: str
    crr: float
    color: tuple[int, int, int]


GREEN = SurfaceType("green", 0.12, (60, 150, 72))
FAIRWAY = SurfaceType("calle", 0.25, (90, 180, 83))
ROUGH = SurfaceType("hierba alta", 0.55, (37, 112, 55))
SAND = SurfaceType("arena", 0.90, (216, 190, 122))
WATER = SurfaceType("agua", 0.05, (45, 116, 190))

#Rectangulo en coordenadas del mundo, con valores flotantes en metros
@dataclass(frozen=True)
class RectF:
    x: float
    y: float
    w: float
    h: float

    def collidepoint(self, x: float, y: float) -> bool:
        return self.x <= x <= self.x + self.w and self.y <= y <= self.y + self.h

    def __iter__(self):
        yield self.x
        yield self.y
        yield self.w
        yield self.h

#Rectangulo de terreno con un coeficiente de rodadura propio
@dataclass
class SurfaceZone:
    rect_m: RectF
    surface: SurfaceType

    def contains(self, position_m: Vec2d) -> bool:
        return self.rect_m.collidepoint(position_m.x, position_m.y)

    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.rect(screen, self.surface.color, rect_to_px(self.rect_m))


#Obstaculo rectangular estatico construido con cuatro segmentos
@dataclass
class StaticBox:
    rect_m: RectF
    color: tuple[int, int, int]
    segments: list[pymunk.Segment]

    @classmethod
    def create(
        cls,
        space: pymunk.Space,
        rect_m: RectF,
        color: tuple[int, int, int] = (116, 75, 46),
        radius: float = 0.012,
        elasticity: float = OBSTACLE_ELASTICITY,
    ) -> "StaticBox":
        x, y, w, h = rect_m
        points = [
            Vec2d(x, y),
            Vec2d(x + w, y),
            Vec2d(x + w, y + h),
            Vec2d(x, y + h),
        ]
        segments: list[pymunk.Segment] = []
        for a, b in zip(points, points[1:] + points[:1]):
            segment = pymunk.Segment(space.static_body, a, b, radius)
            segment.elasticity = elasticity
            segment.friction = WALL_FRICTION
            space.add(segment)
            segments.append(segment)
        return cls(rect_m=rect_m, color=color, segments=segments)

    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.rect(screen, self.color, rect_to_px(self.rect_m), border_radius=7)

#Datos de un nuvel
@dataclass
class LevelData:
    name: str
    start: tuple[float, float]
    hole: tuple[float, float]
    zones: list[SurfaceZone]
    obstacles: list[RectF]

#Bola dinamica y sus operaciones
class GolfBall:
    def __init__(self, space: pymunk.Space, start_position: tuple[float, float]) -> None:
        self.space = space
        moment = pymunk.moment_for_circle(BALL_MASS, 0.0, BALL_RADIUS)
        self.body = pymunk.Body(BALL_MASS, moment)
        self.body.position = start_position
        self.shape = pymunk.Circle(self.body, BALL_RADIUS)
        self.shape.elasticity = BALL_ELASTICITY
        self.shape.friction = BALL_FRICTION
        space.add(self.body, self.shape)

    @property
    def position(self) -> Vec2d:
        return Vec2d(self.body.position.x, self.body.position.y)

    @property
    def speed(self) -> float:
        return self.body.velocity.length

    def reset(self, position: tuple[float, float]) -> None:
        self.body.position = position
        self.body.velocity = (0, 0)
        self.body.angular_velocity = 0.0
        self.body.angle = 0.0
        self.body.force = (0, 0)
        self.body.torque = 0.0

    def is_stopped(self) -> bool:
        return self.speed < STOP_SPEED

    #Aplicar impulso en la direccion indicada
    def strike(self, direction: Vec2d, strength: float) -> None:
        if direction.length <= 1e-9:
            return
        impulse = direction.normalized() * min(MAX_IMPULSE, max(0.0, strength))
        self.body.apply_impulse_at_world_point(impulse, self.body.position)

    #Aplicar una fuerza de rodadura opuesta a la velocudad
    def apply_rolling_resistance(self, crr: float, dt: float) -> None:
        # El modulo fisico usado es Fr = Crr * m * g. Para evitar que la bola invierta
        # artificialmente su velocidad en un paso, se limita la fuerza al valor necesario
        # para detenerla durante dt.
        velocity = Vec2d(self.body.velocity.x, self.body.velocity.y)
        speed = velocity.length
        if speed < STOP_SPEED:
            self.body.velocity = (0, 0)
            self.body.angular_velocity = 0.0
            return

        normal = self.body.mass * G
        friction_force = crr * normal
        stopping_force = self.body.mass * speed / dt
        force_magnitude = min(friction_force, stopping_force)
        force = -velocity.normalized() * force_magnitude
        self.body.apply_force_at_world_point(force, self.body.position)

        # Velocidad angular visual de rodadura.
        # En rodadura pura se cumple v = omega * R, luego omega = v / R.
        # Como la simulacion es cenital, este giro no es la rotacion 3D real de una
        # esfera, sino una aproximacion visual para que la marca de la bola ruede.
        target_omega = speed / BALL_RADIUS
        sign = -1.0 if velocity.x < 0 else 1.0
        self.body.angular_velocity = (
            (1.0 - ROLL_SPIN_SMOOTHING) * self.body.angular_velocity
            + ROLL_SPIN_SMOOTHING * sign * target_omega
        )

    def draw(self, screen: pygame.Surface) -> None:
        pos_px = world_to_screen(self.body.position)
        radius_px = max(4, int(BALL_RADIUS * PX_M))
        pygame.draw.circle(screen, (245, 245, 242), pos_px, radius_px)
        pygame.draw.circle(screen, (210, 210, 205), pos_px, radius_px, 1)

        marker_radius = max(2, radius_px // 4)
        marker_offset = Vec2d(radius_px * 0.48, 0).rotated(self.body.angle)
        marker = (int(pos_px[0] + marker_offset.x), int(pos_px[1] + marker_offset.y))
        pygame.draw.circle(screen, (35, 35, 35), marker, marker_radius)

#Control de bucle principal, nivel e interaccion
class MinigolfGame:
    def __init__(self) -> None:
        pygame.init()
        pygame.display.set_caption("Minigolf fisico 2D - Pymunk")
        self.screen = pygame.display.set_mode((SCREEN_W, SCREEN_H))
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont("Arial", 19)
        self.big_font = pygame.font.SysFont("Arial", 28, bold=True)

        self.levels = build_levels()
        self.level_index = 0
        self.space = pymunk.Space()
        self.space.gravity = (0, 0)
        self.space.iterations = 24

        self.ball: GolfBall
        self.walls: list[pymunk.Segment] = []
        self.obstacles: list[StaticBox] = []
        self.golpes = 0
        self.penalties = 0
        self.message = "Arrastra desde la bola para apuntar."
        self.aiming = False
        self.aim_start = Vec2d(0, 0)
        self.aim_current = Vec2d(0, 0)

        self.load_level(0)

    @property
    def level(self) -> LevelData:
        return self.levels[self.level_index]

    def load_level(self, index: int) -> None:
        self.level_index = index % len(self.levels)
        self.space = pymunk.Space()
        self.space.gravity = (0, 0)
        self.space.iterations = 24
        self._create_outer_walls()
        self.obstacles = [StaticBox.create(self.space, rect) for rect in self.level.obstacles]
        self.ball = GolfBall(self.space, self.level.start)
        self.golpes = 0
        self.penalties = 0
        self.message = f"Nivel {self.level_index + 1}: {self.level.name}"
        self.aiming = False

    def _create_outer_walls(self) -> None:
        margin = 0.02
        points = [
            Vec2d(margin, margin),
            Vec2d(COURSE_W_M - margin, margin),
            Vec2d(COURSE_W_M - margin, COURSE_H_M - margin),
            Vec2d(margin, COURSE_H_M - margin),
        ]
        self.walls = []
        for a, b in zip(points, points[1:] + points[:1]):
            wall = pymunk.Segment(self.space.static_body, a, b, 0.015)
            wall.elasticity = WALL_ELASTICITY
            wall.friction = WALL_FRICTION
            self.space.add(wall)
            self.walls.append(wall)

    def run(self) -> None:
        running = True
        while running:
            running = self._handle_events()
            self._update()
            self._draw()
            self.clock.tick(FPS)
        pygame.quit()

    def _handle_events(self) -> bool:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    return False
                if event.key == pygame.K_r:
                    self.load_level(self.level_index)
                if event.key == pygame.K_n:
                    self.load_level(self.level_index + 1)
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                self._start_aim(event.pos)
            if event.type == pygame.MOUSEMOTION and self.aiming:
                self.aim_current = screen_to_world(event.pos)
            if event.type == pygame.MOUSEBUTTONUP and event.button == 1 and self.aiming:
                self._release_shot(event.pos)
        return True

    def _start_aim(self, mouse_pos_px: tuple[int, int]) -> None:
        if not self.ball.is_stopped():
            self.message = "Espera a que la bola se detenga."
            return
        mouse_m = screen_to_world(mouse_pos_px)
        if mouse_m.get_distance(self.ball.position) > 0.18:
            self.message = "Empieza el arrastre cerca de la bola."
            return
        self.aiming = True
        self.aim_start = self.ball.position
        self.aim_current = mouse_m

    def _release_shot(self, mouse_pos_px: tuple[int, int]) -> None:
        self.aiming = False
        self.aim_current = screen_to_world(mouse_pos_px)
        drag_vector = self.aim_start - self.aim_current
        drag_distance = min(drag_vector.length, MAX_DRAG_DISTANCE_M)
        if drag_distance < 0.03:
            self.message = "Golpe demasiado pequeno."
            return
        strength = MAX_IMPULSE * drag_distance / MAX_DRAG_DISTANCE_M
        self.ball.strike(drag_vector, strength)
        self.golpes += 1
        self.message = f"Golpe {self.golpes}: impulso {strength:.3f} N s"

    def _update(self) -> None:
        sub_dt = DT / SUBSTEPS
        for _ in range(SUBSTEPS):
            surface = self.surface_at_ball()
            if surface is WATER:
                self._apply_water_penalty()
                break
            self.ball.apply_rolling_resistance(surface.crr, sub_dt)
            self.space.step(sub_dt)
        self._check_hole()

    def surface_at_ball(self) -> SurfaceType:
        for zone in reversed(self.level.zones):
            if zone.contains(self.ball.position):
                return zone.surface
        return GREEN

    def _apply_water_penalty(self) -> None:
        self.penalties += WATER_PENALTY
        self.golpes += WATER_PENALTY
        self.ball.reset(self.level.start)
        self.message = "Agua: penalizacion y vuelta al inicio."

    def _check_hole(self) -> None:
        hole = Vec2d(*self.level.hole)
        distance = self.ball.position.get_distance(hole)
        # Criterio de embocada:
        # 1) criterio geometrico: el centro de la bola debe entrar en una zona
        #    interior del hoyo, no basta con tocar visualmente el borde;
        # 2) criterio cinematico: la velocidad debe ser suficientemente baja.
        # Asi se evita que una bola rapida que cruza por encima del hoyo se capture
        # de forma poco realista.
        capture_radius = HOLE_RADIUS * HOLE_CAPTURE_RADIUS_FACTOR
        if distance <= capture_radius and self.ball.speed <= HOLE_CAPTURE_SPEED:
            total = self.golpes
            self.ball.reset(self.level.start)
            self.message = f"Embocada en {total} golpes. Pulsa N para otro nivel."

    def _draw(self) -> None:
        self.screen.fill(BACKGROUND)
        self._draw_course()
        self._draw_panel()
        pygame.display.flip()

    def _draw_course(self) -> None:
        for zone in self.level.zones:
            zone.draw(self.screen)

        pygame.draw.rect(self.screen, (85, 54, 35), (0, 0, SCREEN_W, int(COURSE_H_M * PX_M)), width=8)

        for obstacle in self.obstacles:
            obstacle.draw(self.screen)

        self._draw_hole()
        self.ball.draw(self.screen)
        if self.aiming:
            self._draw_aim()

    def _draw_hole(self) -> None:
        center = world_to_screen(self.level.hole)
        radius = int(HOLE_RADIUS * PX_M)
        pygame.draw.circle(self.screen, (15, 15, 15), center, radius)
        pygame.draw.circle(self.screen, (245, 245, 245), center, radius, 1)
        flag_top = (center[0], center[1] - 55)
        pygame.draw.line(self.screen, (245, 245, 245), center, flag_top, 2)
        pygame.draw.polygon(
            self.screen,
            (225, 48, 48),
            [flag_top, (flag_top[0] + 32, flag_top[1] + 9), (flag_top[0], flag_top[1] + 18)],
        )

    def _draw_aim(self) -> None:
        ball_px = world_to_screen(self.aim_start)
        current_px = world_to_screen(self.aim_current)
        shot_vector = self.aim_start - self.aim_current
        length = min(shot_vector.length, MAX_DRAG_DISTANCE_M)
        direction = shot_vector.normalized() if shot_vector.length > 1e-9 else Vec2d(1, 0)
        target = self.aim_start + direction * length * 0.75
        target_px = world_to_screen(target)

        pygame.draw.line(self.screen, AIM_COLOR, current_px, ball_px, 2)
        pygame.draw.line(self.screen, (255, 220, 80), ball_px, target_px, 4)
        pygame.draw.circle(self.screen, (255, 220, 80), target_px, 5)

    def _draw_panel(self) -> None:
        y0 = int(COURSE_H_M * PX_M)
        pygame.draw.rect(self.screen, PANEL_COLOR, (0, y0, SCREEN_W, PANEL_H_PX))

        surface = self.surface_at_ball()
        speed = self.ball.speed
        lines = [
            f"{self.level.name}   |   Golpes: {self.golpes}   |   Superficie: {surface.name} (Crr={surface.crr:.2f})",
            f"Velocidad: {speed:.2f} m/s   |   R reinicia   N cambia nivel   ESC sale",
            self.message,
        ]
        for i, line in enumerate(lines):
            font = self.big_font if i == 0 else self.font
            text = font.render(line, True, TEXT_COLOR)
            self.screen.blit(text, (18, y0 + 12 + i * 27))


# =============================================================================
# Construccion de niveles
# =============================================================================

def build_levels() -> list[LevelData]:
    full_green = SurfaceZone(RectF(0, 0, COURSE_W_M, COURSE_H_M), GREEN)

    level_1 = LevelData(
        name="Nivel 1",
        start=(0.35, 1.08),
        hole=(3.20, 1.05),
        zones=[
            full_green,
            SurfaceZone(RectF(0.00, 0.00, COURSE_W_M, 0.38), ROUGH),
            SurfaceZone(RectF(0.00, 1.76, COURSE_W_M, 0.39), ROUGH),
            SurfaceZone(RectF(1.25, 0.78, 0.52, 0.58), SAND),
        ],
        obstacles=[
            RectF(1.85, 0.42, 0.12, 0.72),
            RectF(1.85, 1.35, 0.12, 0.38),
        ],
    )

    level_2 = LevelData(
        name="Nivel 2",
        start=(0.32, 1.82),
        hole=(3.20, 0.34),
        zones=[
            full_green,
            SurfaceZone(RectF(1.05, 0.62, 0.95, 0.48), WATER),
            SurfaceZone(RectF(2.05, 1.34, 0.84, 0.44), SAND),
            SurfaceZone(RectF(0.00, 0.00, 0.48, COURSE_H_M), FAIRWAY),
        ],
        obstacles=[
            RectF(0.78, 0.30, 0.16, 1.25),
            RectF(1.58, 1.18, 0.16, 0.76),
            RectF(2.36, 0.20, 0.16, 0.82),
        ],
    )

    level_3 = LevelData(
        name="Nivel 3",
        start=(0.36, 0.36),
        hole=(3.22, 1.78),
        zones=[
            full_green,
            SurfaceZone(RectF(0.00, 1.22, 1.30, 0.93), FAIRWAY),
            SurfaceZone(RectF(1.18, 0.00, 0.56, 0.72), ROUGH),
            SurfaceZone(RectF(2.18, 0.62, 0.64, 0.58), SAND),
            SurfaceZone(RectF(2.90, 0.00, 0.36, 1.20), ROUGH),
        ],
        obstacles=[
            RectF(0.82, 0.82, 0.88, 0.12),
            RectF(1.72, 1.10, 0.12, 0.72),
            RectF(2.42, 1.48, 0.60, 0.12),
        ],
    )

    return [level_1, level_2, level_3]


# =============================================================================
# Conversion entre mundo fisico y pantalla
# =============================================================================


def world_to_screen(point_m: Iterable[float] | Vec2d) -> tuple[int, int]:
    x, y = point_m
    return int(x * PX_M), int(y * PX_M)


def screen_to_world(point_px: tuple[int, int]) -> Vec2d:
    x, y = point_px
    y = min(y, int(COURSE_H_M * PX_M))
    return Vec2d(x / PX_M, y / PX_M)


def rect_to_px(rect_m: RectF) -> pygame.Rect:
    return pygame.Rect(
        int(rect_m.x * PX_M),
        int(rect_m.y * PX_M),
        int(rect_m.w * PX_M),
        int(rect_m.h * PX_M),
    )


if __name__ == "__main__":
    try:
        MinigolfGame().run()
    except KeyboardInterrupt:
        pygame.quit()
        sys.exit(0)
