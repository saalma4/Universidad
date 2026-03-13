from python.grammar.produce import produce

# Nombre de la gramática que añadiste al JSON
nombre_gramatica = 'gramatica_salma'

print(f"--- Probando la gramática:  ---")

# Generamos 10 cadenas
# num_strings: número de cadenas a generar
# max_derivation: pasos máximos para no entrar en bucle (el default es 1000)
resultados = produce(nombre_gramatica, 10)

print("\n--- Cadenas generadas finales ---")
for i, cadena in enumerate(resultados, 1):
    print(f"Cadena {i}: {cadena}")