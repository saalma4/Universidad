import pymunk

# 1. Crear el espacio de simulación
espacio = pymunk.Space()
espacio.gravity = (0, -900)  # Gravedad hacia abajo (eje Y)

# 2. Crear el suelo (una línea estática)
suelo = pymunk.Segment(espacio.static_body, (0, 50), (500, 50), 5)
suelo.elasticity = 0.9  # Muy elástico para que rebote mucho
espacio.add(suelo)

# 3. Crear una pelota (cuerpo dinámico)
masa = 1
radio = 25
momento = pymunk.moment_for_circle(masa, 0, radio) # Calcula cómo gira
cuerpo_pelota = pymunk.Body(masa, momento)
cuerpo_pelota.position = (250, 400) # Empieza en el aire

forma_pelota = pymunk.Circle(cuerpo_pelota, radio)
forma_pelota.elasticity = 0.9
espacio.add(cuerpo_pelota, forma_pelota)

# 4. Simular la caída paso a paso
print("Simulando caída de la pelota...")
print(f"{'Tiempo':<10} | {'Altura (Y)':<10}")
print("-" * 25)

for i in range(20):
    # Avanzamos la simulación 0.02 segundos en cada paso
    espacio.step(0.02)
    print(f"{i*0.02:>9.2f}s | {cuerpo_pelota.position.y:>9.2f}px")

print("\n✅ Si los números de Altura (Y) han bajado y luego subido, ¡el rebote funciona!")