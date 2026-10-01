import pandas as pd
import matplotlib.pyplot as plt

# 1. Leer el archivo CSV
# Puedes reemplazar 'tus_datos.csv' por el nombre real de tu archivo
df = pd.read_csv('comparaciones_busqueda.csv')

# 2. Crear la figura y el gráfico
plt.figure(figsize=(10, 6))

# Graficar Búsqueda Lineal
plt.plot(df['n'], df['lineal_max_comp'], marker='o', label='Búsqueda Lineal (Max)', color='crimson', linewidth=2)

# Graficar Búsqueda Binaria
plt.plot(df['n'], df['binaria_max_comp'], marker='s', label='Búsqueda Binaria (Max)', color='dodgerblue', linewidth=2)

# Graficar Cota Teórica (notarás que se encima con la binaria porque son idénticas)
plt.plot(df['n'], df['cota_teorica'], marker='x', linestyle='--', label='Cota Teórica $\log_2(n)$', color='darkorange', linewidth=1.5)

# 3. Personalización crucial para tus datos
plt.xscale('log') # Escala logarítmica en X para que el salto de 10 a 1,000,000 se vea perfecto

# 4. Títulos y etiquetas
plt.title('Comparación de Complejidad: Búsqueda Lineal vs. Binaria', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Tamaño del arreglo ($n$ - Escala Logarítmica)', fontsize=12)
plt.ylabel('Número Máximo de Comparaciones', fontsize=12)

# Añadir cuadrícula para facilitar la lectura
plt.grid(True, which="both", linestyle='--', alpha=0.5)

# Mostrar la leyenda para identificar cada línea
plt.legend(fontsize=11)

# Ajustar diseño y mostrar
plt.tight_layout()
plt.show()
