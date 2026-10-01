# Actividad 2: Tabla empírica de comparaciones — Búsqueda Lineal vs Binaria

**Curso:** Algoritmos y Estructuras de Datos — SIS210  
**Práctica:** PC1 — Recursividad, Recurrencias y Divide y Vencerás  
**Estudiante:** [Apellido Nombre]  
**Fecha:** [Fecha]

---

## 1. Código de referencia

**Python:**

```python
def busqueda_binaria(arr, objetivo):
    bajo, alto, comparaciones = 0, len(arr) - 1, 0
    while bajo <= alto:
        comparaciones += 1
        medio = (bajo + alto) // 2
        if arr[medio] == objetivo:
            return medio, comparaciones
        elif arr[medio] < objetivo:
            bajo = medio + 1
        else:
            alto = medio - 1
    return -1, comparaciones
```

**C++:**

```cpp
std::pair<int,int> busquedaBinaria(const std::vector<int>& arr, int obj) {
    int bajo = 0, alto = (int)arr.size() - 1, comparaciones = 0;
    while (bajo <= alto) {
        comparaciones++;
        int medio = (bajo + alto) / 2;
        if (arr[medio] == obj) return {medio, comparaciones};
        else if (arr[medio] < obj) bajo = medio + 1;
        else alto = medio - 1;
    }
    return {-1, comparaciones};
}
```

## 2. Tabla de comparaciones empíricas

Se mide el **máximo** número de comparaciones para todos los objetivos posibles en un arreglo ordenado de tamaño `n`.

| n | Búsqueda lineal (max comp.) | Búsqueda binaria (max comp.) | Cota teórica $\lceil \log_2(n+1) \rceil$ | ¿Cota cumplida? |
|----:|----------------------------:|-----------------------------:|------------------------------------------:|:---------------:|
| 10 | 10 | 4 | 4 | Sí |
| 100 | 100 | 7 | 7 | Sí |
| 1,000 | 1,000 | 10 | 10 | Sí |
| 10,000 | 10,000 | 14 | 14 | Sí |
| 100,000 | 100,000 | 17 | 17 | Sí |
| 1,000,000 | 1,000,000 | 20 | 20 | Sí |

## 3. Análisis

### 3.1 Búsqueda lineal

- **Complejidad:** $O(n)$
- **Peor caso:** el objetivo está al final del arreglo o no existe → $n$ comparaciones.
- **Crecimiento:** lineal, se duplica al duplicar `n`.

### 3.2 Búsqueda binaria

- **Complejidad:** $O(\log_2 n)$
- **Peor caso:** el objetivo no existe o está en una hoja del árbol de decisión → $\lceil \log_2(n+1) \rceil$ comparaciones.
- **Crecimiento:** logarítmico, suma 1 comparación al duplicar `n`.

### 3.3 Comparación gráfica

```text
Comparaciones
     │
1e6  │                                     ●  Lineal
     │                                    /
     │                                   /
     │                                  /
     │                                 /
     │                                /
     │                               /
     │                              /
     │                             /
     │                            /
     │                           /
     │                          /
     │                         /
     │                        /
     │                       /
 20  │  ●───●───●───●───●───●  Binaria
     │
     └────────────────────────────────────────────
        10   100  1k   10k  100k  1M        n
```

### 3.4 Ratios de mejora

| n | Lineal / Binaria | Factor |
|----:|------------------:|-------:|
| 10 | 10 / 4 | 2.5× |
| 100 | 100 / 7 | 14.3× |
| 1,000 | 1,000 / 10 | 100× |
| 10,000 | 10,000 / 14 | 714× |
| 100,000 | 100,000 / 17 | 5,882× |
| 1,000,000 | 1,000,000 / 20 | 50,000× |

La ventaja de la búsqueda binaria crece **exponencialmente** con `n`.

## 4. Verificación de la cota

La cota teórica es:

$$
C_{\text{max}}(n) = \lceil \log_2(n+1) \rceil
$$

**Demostración intuitiva:** el árbol de decisión de la búsqueda binaria es un árbol binario de altura $h$. Como máximo hay $2^{h} - 1$ nodos internos, y el número de hojas es $n + 1$ (incluyendo el caso "no encontrado"). Por lo tanto:

$$
n + 1 \leq 2^{h} \implies h \geq \log_2(n+1)
$$

Tomando el techo: $h = \lceil \log_2(n+1) \rceil$.

En todos los casos medidos, la cota se cumple con **igualdad**, lo que confirma que la búsqueda binaria es **óptima** en número de comparaciones para búsqueda en arreglos ordenados.

## 5. Salida del CSV generado

Archivo `outputs/comparaciones_busqueda.csv`:

```csv
n,lineal_max_comp,binaria_max_comp,cota_teorica,cumple_cota
10,10,4,4,Si
100,100,7,7,Si
1000,1000,10,10,Si
10000,10000,14,14,Si
100000,100000,17,17,Si
1000000,1000000,20,20,Si
```

## 6. Conclusión

La búsqueda binaria cumple **exactamente** la cota teórica $\lceil \log_2(n+1) \rceil$ en el peor caso. Su ventaja frente a la búsqueda lineal crece sin límite conforme `n` aumenta: para `n = 1,000,000`, es **50,000 veces más rápida** en número de comparaciones. Esto justifica el requisito de ordenar el arreglo previamente ($O(n \log n)$) cuando se realizarán muchas búsquedas.