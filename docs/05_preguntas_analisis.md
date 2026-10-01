# Preguntas de Análisis — PC1 Recursividad, Recurrencias y Divide y Vencerás

**Curso:** Algoritmos y Estructuras de Datos — SIS210  
**Práctica:** PC1 — Recursividad, Recurrencias y Divide y Vencerás  
**Estudiante:** [Apellido Nombre]  
**Fecha:** [Fecha]  
**Entorno:** Python 3.11+ / C++17

---

## Pregunta 1

> **Si se llama a `suma_digitos(0)`, ¿qué debe retornar? ¿Está cubierto por el caso base de su implementación? Si no, ¿cómo se modifica?**

### 1.1 Respuesta directa

`suma_digitos(0)` debe retornar **`0`**, porque la suma de los dígitos del número `0` es, por convención matemática, `0` (el `0` es su único dígito y no aporta valor a la suma).

### 1.2 ¿Está cubierto por el caso base?

Depende de cómo se haya escrito el caso base. Hay dos variantes comunes:

**Variante A — caso base con `n < 10` (la implementada):**

```python
def suma_digitos(n: int) -> int:
    if n < 10:
        return n
    return n % 10 + suma_digitos(n // 10)
```

Aquí **sí está cubierto**, porque `0 < 10` es verdadero y retorna `0` directamente, sin entrar en el caso recursivo. Esta es la variante robusta.

**Variante B — caso base con `n == 0`:**

```python
def suma_digitos(n: int) -> int:
    if n == 0:
        return 0
    return n % 10 + suma_digitos(n // 10)
```

Aquí también está cubierto explícitamente con `n == 0`.

**Variante C — caso base con `n == 0` mal planteado:**

```python
def suma_digitos(n: int) -> int:
    if n == 0:
        return 0
    if n < 10:  # este caso nunca se alcanza para n=0
        return n
    return n % 10 + suma_digitos(n // 10)
```

Sigue siendo correcto para `0`, pero el orden importa. Si en cambio se escribe:

```python
def suma_digitos(n: int) -> int:
    if n < 10 and n != 0:  # exclusión innecesaria y errónea
        return n
    return n % 10 + suma_digitos(n // 10)
```

Entonces `suma_digitos(0)` entraría al caso recursivo y se llamaría a sí misma con `0 // 10 = 0`, produciendo **recursión infinita** y eventualmente un `RecursionError` en Python o un `stack overflow` en C++.

### 1.3 Verificación empírica

En Python:

```python
assert suma_digitos(0) == 0, 'Error: caso base n=0'
print('suma_digitos(0) =', suma_digitos(0))
```

En C++:

```cpp
assert(sumaDigitos(0) == 0);
std::cout << "suma_digitos(0) = " << sumaDigitos(0) << '\n';
```

Salida esperada:

```text
suma_digitos(0) = 0
```

### 1.4 ¿Cómo se modifica si no estuviera cubierto?

Si el caso base fuera solo `n == 0` y no se manejara `n < 10`, entonces para números de un dígito distintos de `0` (por ejemplo, `7`) la recursión seguiría:

```text
suma_digitos(7) → 7 % 10 + suma_digitos(0) = 7 + 0 = 7
```

Funciona, pero es ineficiente porque hace una llamada extra innecesaria. La forma recomendada es mantener `n < 10` como caso base, porque:

- Cubre `0` correctamente.
- Evita una llamada recursiva extra para dígitos individuales.
- Es más legible y autoexplicativa.

### 1.5 Conclusión

`suma_digitos(0)` **debe retornar `0`**, y con la implementación basada en `n < 10` **sí está cubierto** por el caso base. No requiere modificación. Si se usara una condición más estricta que excluyera `0`, habría que agregar explícitamente `if n == 0: return 0` antes del caso recursivo.

---

## Pregunta 2

> **¿Por qué la Búsqueda Binaria REQUIERE que el arreglo esté ordenado? Diseñe un ejemplo donde una búsqueda binaria aplicada a un arreglo desordenado retorne un resultado INCORRECTO (falso negativo o falso positivo).**

### 2.1 Fundamento teórico

La búsqueda binaria se basa en la **propiedad de orden** del arreglo para descartar mitades en cada iteración. Su invariante fundamental es:

> Si `arr` está ordenado ascendentemente y `arr[medio] < objetivo`, entonces **todos** los elementos en `arr[bajo..medio]` son menores que el objetivo, por lo que el objetivo solo puede estar en `arr[medio+1..alto]`.

Esta inferencia **solo es válida si el arreglo está ordenado**. Si no lo está, la comparación `arr[medio] < objetivo` no permite concluir nada sobre los elementos vecinos, y la búsqueda puede descartar regiones que sí contienen el objetivo o aceptar regiones que no lo contienen.

Formalmente, la búsqueda binaria explota la propiedad:

$$
\forall i < j : \text{arr}[i] \leq \text{arr}[j]
$$

Sin esta propiedad, el descarte de mitades es una **decisión arbitraria** que puede llevar a resultados incorrectos.

### 2.2 Ejemplo de falso negativo

Consideremos el arreglo **desordenado**:

```python
arr = [3, 1, 2]
objetivo = 3
```

Aplicamos la búsqueda binaria paso a paso:

| Iteración | `bajo` | `alto` | `medio` | `arr[medio]` | Comparación | Acción |
|-----------|--------|--------|---------|--------------|-------------|--------|
| 1 | 0 | 2 | 1 | 1 | `1 < 3` | `bajo = 2` |
| 2 | 2 | 2 | 2 | 2 | `2 < 3` | `bajo = 3` |
| — | 3 | 2 | — | — | `bajo > alto` | Termina |

Resultado: **`-1` (no encontrado)**.

Pero el `3` **sí está** en el arreglo (índice 0). Esto es un **falso negativo**.

### 2.3 Ejemplo de falso positivo

La búsqueda binaria no suele dar falsos positivos en el sentido estricto de retornar un índice que no contiene el objetivo, porque solo retorna cuando `arr[medio] == objetivo`. Sin embargo, puede dar un **falso positivo estructural** en variantes que retornan el "punto de inserción" o en búsquedas que asumen orden para decidir vecinos.

Consideremos:

```python
arr = [10, 3, 5, 7, 9]
objetivo = 5
```

Pasos:

| Iteración | `bajo` | `alto` | `medio` | `arr[medio]` | Comparación | Acción |
|-----------|--------|--------|---------|--------------|-------------|--------|
| 1 | 0 | 4 | 2 | 5 | `5 == 5` | Retorna índice 2 |

Aquí acierta por casualidad. Pero si el objetivo fuera `7`:

| Iteración | `bajo` | `alto` | `medio` | `arr[medio]` | Comparación | Acción |
|-----------|--------|--------|---------|--------------|-------------|--------|
| 1 | 0 | 4 | 2 | 5 | `5 < 7` | `bajo = 3` |
| 2 | 3 | 4 | 3 | 7 | `7 == 7` | Retorna índice 3 |

También acierta por casualidad. Pero si el objetivo fuera `9`:

| Iteración | `bajo` | `alto` | `medio` | `arr[medio]` | Comparación | Acción |
|-----------|--------|--------|---------|--------------|-------------|--------|
| 1 | 0 | 4 | 2 | 5 | `5 < 9` | `bajo = 3` |
| 2 | 3 | 4 | 3 | 7 | `7 < 9` | `bajo = 4` |
| 3 | 4 | 4 | 4 | 9 | `9 == 9` | Retorna índice 4 |

Acierta. El problema es que estos aciertos son **coincidencias**, no garantías. Un contraejemplo claro de falso negativo es el primero: `[3, 1, 2]` con objetivo `3`.

### 2.4 Demostración formal del fallo

La búsqueda binaria asume el invariante:

$$
\text{si } \text{arr}[\text{medio}] < \text{objetivo}, \text{ entonces } \text{objetivo} \notin \text{arr}[\text{bajo}..\text{medio}]
$$

Esta implicación es **válida solo si el arreglo está ordenado**. En un arreglo desordenado, puede ocurrir que:

$$
\text{arr}[\text{medio}] < \text{objetivo} \quad \text{y} \quad \exists\, i \in [\text{bajo}, \text{medio}] : \text{arr}[i] = \text{objetivo}
$$

En el ejemplo `[3, 1, 2]` con objetivo `3`:

- `bajo = 0`, `alto = 2`, `medio = 1`
- `arr[1] = 1 < 3` → se descarta `arr[0..1]`
- Pero `arr[0] = 3 = objetivo` → **falso negativo**

### 2.5 Implicaciones prácticas

| Aspecto | Arreglo ordenado | Arreglo desordenado |
|---------|------------------|---------------------|
| Descarte de mitades | Correcto | Incorrecto |
| Garantía de búsqueda | Sí | No |
| Complejidad | $O(\log n)$ | No aplica |
| Resultado | Correcto | Puede ser falso negativo |
| Requisito previo | Ordenar ($O(n \log n)$) | — |

### 2.6 Conclusión

La búsqueda binaria **requiere** que el arreglo esté ordenado porque su estrategia de descarte de mitades se basa en la transitividad del orden. Sin esa propiedad, puede descartar regiones que contienen el objetivo y retornar `-1` incorrectamente (falso negativo), como se demostró con `[3, 1, 2]` buscando `3`. La solución es ordenar primero, lo que añade un costo $O(n \log n)$ pero permite búsquedas repetidas en $O(\log n)$.

---

## Pregunta 3

> **En la recurrencia (c) $T(n) = 2T(n/2) + O(n^{2})$, el Caso 3 del Teorema Maestro implica que el trabajo local $O(n^{2})$ domina. ¿Qué algoritmo real podría tener esta recurrencia? ¿Es preferible a Merge Sort?**

### 3.1 Análisis de la recurrencia

Parámetros:

- $a = 2$
- $b = 2$
- $f(n) = O(n^{2})$

Exponente crítico:

$$
c = \log_b a = \log_2 2 = 1
$$

Comparación:

$$
f(n) = O(n^{2}) = \Omega\!\left(n^{1 + \varepsilon}\right) \quad \text{con } \varepsilon = 1
$$

Verificación de regularidad:

$$
a \cdot f\!\left(\frac{n}{b}\right) = 2 \cdot \left(\frac{n}{2}\right)^{2} = 2 \cdot \frac{n^{2}}{4} = \frac{n^{2}}{2} \leq k \cdot n^{2} \quad \text{con } k = \tfrac{1}{2} < 1
$$

Por lo tanto, aplica el **Caso 3**:

$$
T(n) = \Theta\!\left(n^{2}\right)
$$

El trabajo local cuadrático domina sobre las llamadas recursivas, cuyo costo agregado es $O(n^{\log_2 2}) = O(n)$.

### 3.2 ¿Qué algoritmo real podría tener esta recurrencia?

Esta recurrencia describe un esquema de **divide y vencerás** donde:

- El problema se divide en **2 subproblemas** de tamaño $n/2$.
- El paso de **combinación (merge)** tiene costo $O(n^{2})$.

**Algoritmo candidato 1: Merge Sort con merge cuadrático.**

Si en lugar de fusionar dos subarreglos ordenados en $O(n)$ usando dos punteros, se fusionaran insertando cada elemento del subarreglo derecho en su posición correcta del izquierdo mediante **búsqueda lineal** (que es $O(n)$ por inserción), el merge costaría $O(n^{2})$. Este es un Merge Sort "mal implementado".

**Algoritmo candidato 2: Variante de ordenamiento por inserción recursiva.**

Un algoritmo que divide el arreglo en dos mitades, ordena cada mitad recursivamente, y luego las combina insertando cada elemento de una mitad en la otra con un método cuadrático.

**Algoritmo candidato 3: Multiplicación de matrices con combinación ingenua.**

La multiplicación de matrices por divide y vencerás (algoritmo de Strassen mal implementado, sin la optimización de las 7 multiplicaciones) tiene recurrencia $T(n) = 8T(n/2) + O(n^{2})$, que da $O(n^{3})$. Si se reduce a $2$ llamadas pero se mantiene la combinación cuadrática, se obtiene $T(n) = 2T(n/2) + O(n^{2})$.

**Algoritmo candidato 4: Closest Pair of Points (versión ingenua).**

El problema de encontrar el par de puntos más cercano se resuelve con divide y vencerás en $O(n \log n)$ usando una franja y ordenamiento por $y$. Si la combinación se hace comparando **todos los pares** de la franja, el costo de combinación se vuelve $O(n^{2})$ y la recurrencia resultante es $T(n) = 2T(n/2) + O(n^{2})$, dando $O(n^{2})$.

### 3.3 ¿Es preferible a Merge Sort?

**No, no es preferible.** Comparación asintótica:

| Algoritmo | Recurrencia | Complejidad |
|-----------|-------------|-------------|
| Merge Sort estándar | $T(n) = 2T(n/2) + O(n)$ | $\Theta(n \log n)$ |
| Merge Sort con merge cuadrático | $T(n) = 2T(n/2) + O(n^{2})$ | $\Theta(n^{2})$ |

Para $n$ suficientemente grande:

$$
n \log n \ll n^{2}
$$

Por ejemplo, para $n = 1{,}000{,}000$:

- $n \log_2 n \approx 20{,}000{,}000$ operaciones
- $n^{2} = 1{,}000{,}000{,}000{,}000$ operaciones

La diferencia es de **5 órdenes de magnitud**. El Merge Sort estándar es asintóticamente muy superior.

### 3.4 ¿Cuándo podría ser aceptable?

Solo en casos donde:

- $n$ es muy pequeño (por ejemplo, $n < 50$), donde el overhead constante del merge lineal podría no compensar.
- El costo de comparación entre elementos es extremadamente alto y el merge cuadrático permite menos comparaciones totales (poco común).
- Se requiere **estabilidad** y el merge cuadrático la preserva, pero el merge lineal también.

En la práctica, **nunca se elige un merge cuadrático** sobre uno lineal. La única justificación sería didáctica: mostrar cómo el Teorema Maestro captura el impacto del trabajo local en la complejidad total.

### 3.5 Conclusión

La recurrencia $T(n) = 2T(n/2) + O(n^{2})$ corresponde a un esquema de divide y vencerás con **combinación cuadrática**, como un Merge Sort mal implementado o una variante ingenua de Closest Pair. **No es preferible a Merge Sort** porque su complejidad $\Theta(n^{2})$ es asintóticamente mucho peor que $\Theta(n \log n)$. El Teorema Maestro permite identificar rápidamente que el trabajo local domina y determina la complejidad total.

---

## Pregunta 4

> **¿Cuál es el peor caso para Merge Sort en términos de comparaciones? ¿Y el mejor caso? A diferencia de Quick Sort, ¿siempre produce el mismo número de operaciones dado $n$?**

### 4.1 Número de comparaciones en Merge Sort

Merge Sort sigue la recurrencia:

$$
C(n) = C(\lfloor n/2 \rfloor) + C(\lceil n/2 \rceil) + M(n)
$$

donde $M(n)$ es el número de comparaciones en el paso de merge de dos subarreglos que suman $n$ elementos.

En el **merge** de dos arreglos de tamaños $p$ y $q$:

- **Mejor caso:** se realizan $\min(p, q)$ comparaciones. Ocurre cuando todos los elementos de un subarreglo son menores que todos los del otro, y el merge termina cuando uno se agota.
- **Peor caso:** se realizan $p + q - 1 = n - 1$ comparaciones. Ocurre cuando los elementos se intercalan de modo que ninguno se agota hasta el final.

### 4.2 Análisis del mejor caso

Para que el merge haga el mínimo de comparaciones en cada nivel, los subarreglos deben estar "separados" (todos los de uno menores que todos los del otro). Esto es posible si la entrada ya está ordenada de cierta forma.

En el mejor caso, el número total de comparaciones es:

$$
C_{\text{mejor}}(n) = \sum_{i=1}^{\log_2 n} \frac{n}{2^{i}} \cdot \min\!\left(\frac{n}{2^{i}}, \frac{n}{2^{i}}\right) \cdot 2^{i-1}
$$

Simplificando, el mejor caso conocido para Merge Sort es:

$$
C_{\text{mejor}}(n) = \Theta(n \log n)
$$

Pero con una constante menor que en el peor caso. El mejor caso exacto es aproximadamente:

$$
C_{\text{mejor}}(n) \approx \frac{n}{2} \log_2 n
$$

### 4.3 Análisis del peor caso

El peor caso ocurre cuando en cada merge los elementos se intercalan de modo que se necesitan $n - 1$ comparaciones. Esto sucede cuando la entrada tiene una estructura alternante.

El número total de comparaciones en el peor caso es:

$$
C_{\text{peor}}(n) = n \lceil \log_2 n \rceil - 2^{\lceil \log_2 n \rceil} + 1
$$

Para $n$ potencia de 2:

$$
C_{\text{peor}}(n) = n \log_2 n - n + 1
$$

Por lo tanto:

$$
C_{\text{peor}}(n) = \Theta(n \log n)
$$

### 4.4 Tabla comparativa

| $n$ | Mejor caso ($\approx \frac{n}{2}\log_2 n$) | Peor caso ($n\log_2 n - n + 1$) |
|-----|---------------------------------------------|----------------------------------|
| 2 | 1 | 1 |
| 4 | 4 | 5 |
| 8 | 12 | 17 |
| 16 | 32 | 49 |
| 32 | 80 | 129 |
| 1024 | 5,120 | 9,217 |
| 1,048,576 | 10,485,760 | 20,971,521 |

### 4.5 ¿Siempre produce el mismo número de operaciones dado $n$?

**No exactamente.** Merge Sort no siempre realiza el mismo número de comparaciones para un $n$ dado. Depende de la **distribución de los datos**:

- **Mejor caso:** $\approx \frac{n}{2} \log_2 n$ comparaciones.
- **Peor caso:** $\approx n \log_2 n - n + 1$ comparaciones.
- **Caso promedio:** $\approx n \log_2 n - 1.26 n$ comparaciones.

Sin embargo, la **diferencia entre mejor y peor caso es solo un factor constante** (aproximadamente 2). Ambos son $\Theta(n \log n)$.

### 4.6 Comparación con Quick Sort

| Aspecto | Merge Sort | Quick Sort |
|---------|------------|------------|
| Mejor caso | $O(n \log n)$ | $O(n \log n)$ |
| Caso promedio | $O(n \log n)$ | $O(n \log n)$ |
| Peor caso | $O(n \log n)$ | $O(n^{2})$ |
| Estabilidad | Estable | No estable (versión clásica) |
| Memoria extra | $O(n)$ | $O(\log n)$ (pila) |
| N.º de comparaciones para un $n$ dado | Varía en un factor constante (≈2) | Varía drásticamente (de $n\log n$ a $n^{2}$) |
| Dependencia de la entrada | Poca | Alta (elección de pivote) |

**Diferencia clave:** En Merge Sort, el **número de operaciones siempre es $\Theta(n \log n)$**, independientemente de la entrada. En Quick Sort, el peor caso es $\Theta(n^{2})$ y ocurre cuando el pivote elegido es siempre el mínimo o el máximo (por ejemplo, con un arreglo ya ordenado y pivote en el primer elemento).

### 4.7 ¿Por qué Merge Sort es más predecible?

Merge Sort siempre divide el arreglo en dos mitades **exactamente iguales** (o casi iguales), sin importar los valores. Esto garantiza que el árbol de recursión tenga profundidad $\log_2 n$ y que cada nivel haga $O(n)$ trabajo. Quick Sort, en cambio, divide según el pivote, y si el pivote es malo, la división es desbalanceada (1 y $n-1$), lo que lleva a profundidad $n$ y costo $O(n^{2})$.

### 4.8 Número exacto de comparaciones en el peor caso

Para $n = 2^{k}$:

$$
C_{\text{peor}}(n) = n \log_2 n - n + 1
$$

Demostración por inducción:

- **Base:** $n = 1$: $C(1) = 0 = 1 \cdot 0 - 1 + 1 = 0$. ✓
- **Paso inductivo:** $C(n) = 2 C(n/2) + (n - 1)$
  - $= 2\left(\frac{n}{2} \log_2 \frac{n}{2} - \frac{n}{2} + 1\right) + n - 1$
  - $= n \log_2 \frac{n}{2} - n + 2 + n - 1$
  - $= n (\log_2 n - 1) + 1$
  - $= n \log_2 n - n + 1$. ✓

### 4.9 Conclusión

- **Peor caso de Merge Sort:** $n \log_2 n - n + 1 = \Theta(n \log n)$ comparaciones.
- **Mejor caso de Merge Sort:** $\approx \frac{n}{2} \log_2 n = \Theta(n \log n)$ comparaciones.
- **Caso promedio:** $\approx n \log_2 n - 1.26 n = \Theta(n \log n)$.
- **¿Siempre el mismo número de operaciones?** No, pero la variación es solo un factor constante (≈2). A diferencia de Quick Sort, **Merge Sort nunca degrada a $O(n^{2})$**, porque su división no depende de los valores de la entrada. Esto lo hace **predecible y robusto** para aplicaciones donde el peor caso debe estar acotado.

---

## Resumen de respuestas

| # | Pregunta | Respuesta breve |
|---|----------|-----------------|
| 1 | ¿Qué retorna `suma_digitos(0)`? | Retorna `0`. Cubierto por el caso base `n < 10`. |
| 2 | ¿Por qué búsqueda binaria requiere orden? | Porque el descarte de mitades usa transitividad del orden. Ejemplo: `[3, 1, 2]` buscando `3` retorna `-1` (falso negativo). |
| 3 | ¿Qué algoritmo tiene $T(n) = 2T(n/2) + O(n^{2})$? | Merge Sort con merge cuadrático o Closest Pair ingenuo. No es preferible a Merge Sort estándar ($\Theta(n^{2})$ vs $\Theta(n \log n)$). |
| 4 | Peor y mejor caso de Merge Sort | Peor: $n\log_2 n - n + 1$. Mejor: $\approx \frac{n}{2}\log_2 n$. Ambos $\Theta(n \log n)$. No siempre el mismo número, pero variación de solo factor constante. |

---

## Referencias

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4th ed.). MIT Press.
- Knuth, D. E. (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.
- Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.
- Kleinberg, J., & Tardos, É. (2005). *Algorithm Design*. Pearson.