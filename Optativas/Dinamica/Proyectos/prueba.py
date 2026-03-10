import pybullet as p
import pybullet_data
import time

# 1. Conectar con la interfaz gráfica (GUI)
# Si estás en un servidor sin pantalla, usarías p.DIRECT
physicsClient = p.connect(p.GUI)

# 2. Añadir la ruta de los modelos básicos (planos, esferas, robots)
p.setAdditionalSearchPath(pybullet_data.getDataPath())

# 3. Configurar el mundo
p.setGravity(0, 0, -9.81) # Gravedad en el eje Z (3D)
planoId = p.loadURDF("plane.urdf") # Cargamos un suelo

# 4. Crear una esfera manualmente
# Posición inicial (x, y, z)
startPos = [0, 0, 5] 
# Orientación inicial (ángulos en radianes)
startOrientation = p.getQuaternionFromEuler([0, 0, 0])

# Cargamos el modelo de una esfera
sphereId = p.loadURDF("sphere_1cm.urdf", startPos, startOrientation)

# 5. Bucle de simulación
print("Simulación iniciada. Cierra la ventana para terminar.")

for i in range(10000):
    p.stepSimulation() # Avanza un paso la física
    
    # Obtenemos la posición de la esfera para imprimirla
    pos, _ = p.getBasePositionAndOrientation(sphereId)
    if i % 100 == 0: # Imprime cada 100 pasos para no saturar
        print(f"Altura de la esfera: {pos[2]:.2f} metros")
    
    time.sleep(1./240.) # PyBullet funciona por defecto a 240Hz

# 6. Desconectar al terminar
p.disconnect()