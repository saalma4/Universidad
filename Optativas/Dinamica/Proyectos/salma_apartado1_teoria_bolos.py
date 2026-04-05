
"""Apartado 1 del proyecto de bolos.

Calcula y muestra las expresiones teóricas del modelo ideal:
- bola esférica maciza y homogénea
- pista horizontal
- rozamiento cinético constante mientras hay deslizamiento
- velocidad angular inicial configurable (por defecto 0)

Está pensado para acompañar a la memoria y para comprobar números.
"""

import math

# ============================================================
# PARÁMETROS EDITABLES
# ============================================================
MASA = 6.8                 # kg
RADIO = 0.109             # m
MU = 0.18                 # coeficiente de rozamiento cinético
V0 = 8.0                  # m/s
OMEGA0 = 0.0              # rad/s (ideal: 0)
G = 9.81                  # m/s^2

# Esfera maciza homogénea: I = beta * m * R^2 = (2/5) m R^2
BETA = 2.0 / 5.0


def momento_inercia(masa, radio, beta=BETA):
    """Momento de inercia en torno al centro de masas."""
    return beta * masa * radio * radio


def teoria_transicion(v0, omega0, radio, mu, beta=BETA, g=G):
    """
    Devuelve:
    - t_rod: tiempo hasta rodadura pura
    - v_final: velocidad lineal cuando empieza la rodadura pura
    - omega_final: velocidad angular en ese instante
    - distancia: distancia recorrida durante el deslizamiento
    """
    s0 = v0 - omega0 * radio  # velocidad relativa en el punto de contacto

    if abs(s0) < 1e-12:
        # Ya sale en rodadura pura
        return 0.0, v0, v0 / radio, 0.0

    # Fórmula general para I = beta m R^2
    t_rod = beta * abs(s0) / ((1.0 + beta) * mu * g)

    # Signo del deslizamiento inicial:
    # s0 > 0 -> va demasiado rápido para el giro que lleva
    # s0 < 0 -> lleva demasiado giro para la velocidad lineal
    signo = 1.0 if s0 > 0 else -1.0

    a = -signo * mu * g
    alpha = signo * mu * g / (beta * radio)

    v_final = v0 + a * t_rod
    omega_final = omega0 + alpha * t_rod

    # Ajuste limpio para imponer rodadura pura exacta
    omega_final = v_final / radio

    distancia = v0 * t_rod + 0.5 * a * t_rod * t_rod
    return t_rod, v_final, omega_final, distancia


def velocidad_lineal_durante_deslizamiento(t, v0=V0, mu=MU, g=G):
    """Caso ideal clásico con omega0 = 0 y esfera homogénea."""
    return v0 - mu * g * t


def velocidad_angular_durante_deslizamiento(t, radio=RADIO, mu=MU, g=G, beta=BETA):
    """Caso ideal clásico con omega0 = 0 y esfera homogénea."""
    return (mu * g / (beta * radio)) * t


def imprimir_formulas():
    print("=" * 72)
    print("APARTADO 1 - MODELO TEÓRICO IDEAL")
    print("=" * 72)
    print("Suposiciones:")
    print("1) La bola es una esfera maciza homogénea.")
    print("2) La pista es horizontal.")
    print("3) Mientras hay deslizamiento, el rozamiento es cinético: Fr = mu * m * g.")
    print("4) Se desprecia el aire y el rozamiento por rodadura en este primer modelo.")
    print("5) La condición de rodadura pura es v = omega * R.")
    print()

    print("Ecuaciones durante el deslizamiento:")
    print("  a = - signo(v - omega*R) * mu * g")
    print("  alpha = signo(v - omega*R) * mu * g / (beta * R)")
    print("  con beta = I / (m R^2)")
    print()

    print("Caso ideal clásico del enunciado (omega0 = 0, esfera homogénea beta = 2/5):")
    print("  I = (2/5) m R^2")
    print("  v(t) = V0 - mu g t")
    print("  omega(t) = (5 mu g / (2R)) t")
    print("  t_rod = 2 V0 / (7 mu g)")
    print("  v_final = 5 V0 / 7")
    print("  omega_final = v_final / R = 5 V0 / (7R)")
    print()

    print("Fórmula general si la bola sale con giro inicial omega0 y")
    print("si usamos I = beta m R^2:")
    print("  t_rod = beta * |V0 - omega0 R| / ((1 + beta) mu g)")
    print("  v_final = V0 - signo(V0 - omega0 R) * mu g * t_rod")
    print("  omega_final = v_final / R")
    print()


def main():
    imprimir_formulas()

    I = momento_inercia(MASA, RADIO, BETA)
    t_rod, v_final, omega_final, distancia = teoria_transicion(
        V0, OMEGA0, RADIO, MU, BETA, G
    )

    print("=" * 72)
    print("VALORES NUMÉRICOS CON LOS PARÁMETROS ACTUALES")
    print("=" * 72)
    print(f"Masa                 = {MASA:.3f} kg")
    print(f"Radio                = {RADIO:.3f} m")
    print(f"Rozamiento           = {MU:.3f}")
    print(f"Velocidad inicial    = {V0:.3f} m/s")
    print(f"Velocidad angular 0  = {OMEGA0:.3f} rad/s")
    print(f"Momento de inercia   = {I:.6f} kg·m²")
    print()

    print(f"Tiempo hasta rodadura pura   = {t_rod:.6f} s")
    print(f"Velocidad final lineal       = {v_final:.6f} m/s")
    print(f"Velocidad final angular      = {omega_final:.6f} rad/s")
    print(f"Distancia durante deslizam.  = {distancia:.6f} m")
    print()

    # Tabla pequeña para que se vea cómo evolucionan v(t) y omega(t)
    print("=" * 72)
    print("TABLA DE EVOLUCIÓN DURANTE EL DESLIZAMIENTO (caso clásico)")
    print("=" * 72)
    print(f"{'t (s)':>10} {'v(t) (m/s)':>16} {'omega(t) (rad/s)':>20} {'v-omegaR':>14}")
    n = 6
    for i in range(n + 1):
        t = (t_rod * i) / n
        v = velocidad_lineal_durante_deslizamiento(t)
        w = velocidad_angular_durante_deslizamiento(t)
        diff = v - w * RADIO
        print(f"{t:10.4f} {v:16.6f} {w:20.6f} {diff:14.6f}")

    print()
    print("Interpretación física:")
    print("- Mientras desliza, el rozamiento frena la traslación.")
    print("- Ese mismo rozamiento genera un torque que hace girar la bola.")
    print("- La fase de deslizamiento termina cuando el punto de contacto")
    print("  deja de moverse respecto al suelo, es decir, cuando v = omega R.")


if __name__ == "__main__":
    main()
