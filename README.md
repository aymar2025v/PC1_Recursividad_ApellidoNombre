# PC1 — Recursividad, Recurrencias y Divide y Vencerás

**Curso:** Algoritmos y Estructuras de Datos — SIS210  
**Universidad:** Universidad Nacional del Altiplano — Puno  
**Docente:** Dr. Aldo Hernán Zanabria Gálvez  
**Estudiante:** [Apellido Nombre]  
**Semana:** 3  
**Fecha:** [Fecha]

---

## 1. Descripción

Implementación en **Python 3.11+** y **C++17** de los algoritmos solicitados en la Práctica Calificada 1:

1. Suma de dígitos recursiva con traza de pila.
2. Búsqueda binaria con conteo de comparaciones.
3. Merge Sort con benchmark empírico.
4. Resolución de recurrencias mediante el Teorema Maestro.
5. Preguntas de análisis.
6. Investigación sobre Fibonacci Search.

---

## 2. Estructura del proyecto

```text
PC1_Recursividad_ApellidoNombre/
├── PC1_Recursividad_ApellidoNombre.cpp
├── PC1_Recursividad_ApellidoNombre.ipynb
├── README.md
├── .gitignore
├── .vscode/
│   ├── settings.json
│   ├── tasks.json
│   └── launch.json
├── build/
│   └── pc1.exe
├── data/
│   └── codigos_matricula.txt
├── docs/
│   ├── 01_traza_pila_suma_digitos.md
│   ├── 02_tabla_busqueda_binaria.md
│   ├── 03_benchmark_merge_sort.md
│   ├── 04_teorema_maestro.md
│   ├── 05_preguntas_analisis.md
│   └── 06_investigacion_fibonacci_search.md
└── outputs/
    ├── comparaciones_busqueda.csv
    ├── tiempos_benchmark.csv
    └── salidas_*.txt
```

---

## 3. Requisitos

- **Python:** 3.11 o superior
- **C++:** g++ con soporte para C++17
- **Sistema:** Windows 10/11 (probado), Linux, macOS
- **Editor:** Visual Studio Code con extensiones:
  - C/C++
  - Python
  - Jupyter

---

## 4. Compilación y ejecución

### 4.1 C++

```bash
g++ -std=c++17 -O2 -o build/pc1.exe PC1_Recursividad_ApellidoNombre.cpp
.\build\pc1.exe
```

### 4.2 Python

Abrir `PC1_Recursividad_ApellidoNombre.ipynb` en VS Code y ejecutar todas las celdas.

---

## 5. Actividades implementadas

| Actividad | Python | C++ | Documento |
|-----------|:------:|:---:|-----------|
| 1. Suma de dígitos | ✓ | ✓ | `docs/01_traza_pila_suma_digitos.md` |
| 2. Búsqueda binaria | ✓ | ✓ | `docs/02_tabla_busqueda_binaria.md` |
| 3. Merge Sort + benchmark | ✓ | ✓ | `docs/03_benchmark_merge_sort.md` |
| 4. Teorema Maestro | — | — | `docs/04_teorema_maestro.md` |
| Preguntas de análisis | — | — | `docs/05_preguntas_analisis.md` |
| Fibonacci Search | — | — | `docs/06_investigacion_fibonacci_search.md` |

---

## 6. Resultados principales

- **Suma de dígitos:** `suma_digitos(12345) = 15`, profundidad de pila = 5.
- **Búsqueda binaria:** cumple la cota $\lceil \log_2(n+1) \rceil$ en todos los casos.
- **Merge Sort:** $\Theta(n \log n)$, C++ ~20× más rápido que Python.
- **Teorema Maestro:** las 4 recurrencias resueltas cubren los 3 casos.
- **Fibonacci Search:** más comparaciones que búsqueda binaria, pero mejor localidad de caché.

---

## 7. Salidas generadas

- `outputs/comparaciones_busqueda.csv`
- `outputs/tiempos_benchmark.csv`
- `outputs/cpp_actividad1_salida.txt`
- `outputs/cpp_actividad2_salida.txt`
- `outputs/cpp_actividad3_salida.txt`

---

## 8. Referencias

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4th ed.). MIT Press.
- Knuth, D. E. (1998). *The Art of Computer Programming, Volume 3*. Addison-Wesley.
- Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.