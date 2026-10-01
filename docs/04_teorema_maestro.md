# Actividad 4: Teorema Maestro — Resolución de Recurrencias

**Curso:** Algoritmos y Estructuras de Datos — SIS210  
**Práctica:** PC1 — Recursividad, Recurrencias y Divide y Vencerás  
**Estudiante:** [Apellido Nombre]  
**Fecha:** [Fecha]

---

## Recordatorio del Teorema Maestro

Para recurrencias de la forma:

$$
T(n) = a \cdot T\!\left(\frac{n}{b}\right) + f(n), \quad a \geq 1,\ b > 1
$$

se define el exponente crítico:

$$
c = \log_b a
$$

y se comparan $n^{c}$ con $f(n)$:

| Caso | Condición | Solución |
|------|-----------|----------|
| 1 | $f(n) = O\!\left(n^{c - \varepsilon}\right)$ para algún $\varepsilon > 0$ | $T(n) = \Theta\!\left(n^{c}\right)$ |
| 2 | $f(n) = \Theta\!\left(n^{c}\right)$ | $T(n) = \Theta\!\left(n^{c} \log n\right)$ |
| 3 | $f(n) = \Omega\!\left(n^{c + \varepsilon}\right)$ para algún $\varepsilon > 0$, y se cumple la condición de regularidad $a\,f(n/b) \leq k\,f(n)$ con $k < 1$ | $T(n) = \Theta\!\left(f(n)\right)$ |

---

## Recurrencia (a): $T(n) = 4T(n/2) + O(n)$

**Paso 1 — Identificar parámetros:**

- $a = 4$
- $b = 2$
- $f(n) = O(n)$

**Paso 2 — Calcular el exponente crítico:**

$$
c = \log_b a = \log_2 4 = 2
$$

**Paso 3 — Comparar $f(n)$ con $n^{c} = n^{2}$:**

$$
f(n) = O(n) = O\!\left(n^{2 - 1}\right)
$$

Como $f(n)$ es polinómicamente menor que $n^{2}$, aplica el **Caso 1** con $\varepsilon = 1 > 0$.

**Paso 4 — Solución:**

$$
\boxed{T(n) = \Theta\!\left(n^{2}\right)}
$$

**Interpretación:** Las llamadas recursivas dominan el costo. El trabajo local $O(n)$ es despreciable frente al costo de las $4$ llamadas sobre subproblemas de tamaño $n/2$.

---

## Recurrencia (b): $T(n) = T(n/3) + O(1)$

**Paso 1 — Identificar parámetros:**

- $a = 1$
- $b = 3$
- $f(n) = O(1)$

**Paso 2 — Calcular el exponente crítico:**

$$
c = \log_b a = \log_3 1 = 0
$$

**Paso 3 — Comparar $f(n)$ con $n^{c} = n^{0} = 1$:**

$$
f(n) = \Theta(1) = \Theta\!\left(n^{0}\right)
$$

Como $f(n)$ es del mismo orden que $n^{0}$, aplica el **Caso 2**.

**Paso 4 — Solución:**

$$
\boxed{T(n) = \Theta\!\left(n^{0} \log n\right) = \Theta(\log n)}
$$

**Interpretación:** Cada llamada hace trabajo constante y solo hay una llamada recursiva, por lo que la profundidad de recursión es $\log_3 n$ y el costo total es logarítmico.

---

## Recurrencia (c): $T(n) = 2T(n/2) + O(n^{2})$

**Paso 1 — Identificar parámetros:**

- $a = 2$
- $b = 2$
- $f(n) = O(n^{2})$

**Paso 2 — Calcular el exponente crítico:**

$$
c = \log_b a = \log_2 2 = 1
$$

**Paso 3 — Comparar $f(n)$ con $n^{c} = n^{1} = n$:**

$$
f(n) = O(n^{2}) = \Omega\!\left(n^{1 + 1}\right)
$$

Como $f(n)$ es polinómicamente mayor que $n^{1}$, se verifica el **Caso 3** con $\varepsilon = 1 > 0$.

**Verificación de la condición de regularidad:**

$$
a \cdot f\!\left(\frac{n}{b}\right) = 2 \cdot \left(\frac{n}{2}\right)^{2} = 2 \cdot \frac{n^{2}}{4} = \frac{n^{2}}{2} \leq k \cdot n^{2}
$$

Se cumple con $k = \tfrac{1}{2} < 1$. Por lo tanto, el Caso 3 aplica.

**Paso 4 — Solución:**

$$
\boxed{T(n) = \Theta\!\left(n^{2}\right)}
$$

**Interpretación:** El trabajo local cuadrático domina. Un algoritmo real con esta recurrencia podría ser una variante de **Merge Sort** en la cual el paso de combinación (merge) tuviera costo $O(n^{2})$ en lugar de $O(n)$ —por ejemplo, si para fusionar se usara un método de ordenamiento cuadrático. **No es preferible a Merge Sort estándar**, cuyo costo $O(n \log n)$ es asintóticamente menor para $n$ suficientemente grande.

---

## Recurrencia (d): $T(n) = 3T(n/4) + O(n)$

**Paso 1 — Identificar parámetros:**

- $a = 3$
- $b = 4$
- $f(n) = O(n)$

**Paso 2 — Calcular el exponente crítico:**

$$
c = \log_b a = \log_4 3 \approx 0.7925
$$

**Paso 3 — Comparar $f(n)$ con $n^{c} = n^{0.7925}$:**

$$
f(n) = O(n) = \Omega\!\left(n^{0.7925 + \varepsilon}\right)
$$

Podemos tomar, por ejemplo, $\varepsilon \approx 0.2$, ya que $0.7925 + 0.2 = 0.9925 < 1$. Por lo tanto, se verifica el **Caso 3**.

**Verificación de la condición de regularidad:**

$$
a \cdot f\!\left(\frac{n}{b}\right) = 3 \cdot \frac{n}{4} = \frac{3n}{4} \leq k \cdot n
$$

Se cumple con $k = \tfrac{3}{4} < 1$. El Caso 3 aplica.

**Paso 4 — Solución:**

$$
\boxed{T(n) = \Theta(n)}
$$

**Interpretación:** Aunque hay $3$ llamadas recursivas, el factor de reducción $b = 4$ es lo suficientemente grande como para que la suma de los subproblemas crezca más lento que el trabajo local lineal. El trabajo local $O(n)$ domina.

---

## Tabla resumen

| Recurrencia | $a$ | $b$ | $f(n)$ | $c = \log_b a$ | Caso | Solución |
|-------------|----:|----:|--------|---------------:|:----:|----------|
| (a) $T(n) = 4T(n/2) + O(n)$ | 4 | 2 | $O(n)$ | $2$ | 1 | $\Theta(n^{2})$ |
| (b) $T(n) = T(n/3) + O(1)$ | 1 | 3 | $O(1)$ | $0$ | 2 | $\Theta(\log n)$ |
| (c) $T(n) = 2T(n/2) + O(n^{2})$ | 2 | 2 | $O(n^{2})$ | $1$ | 3 | $\Theta(n^{2})$ |
| (d) $T(n) = 3T(n/4) + O(n)$ | 3 | 4 | $O(n)$ | $\approx 0.7925$ | 3 | $\Theta(n)$ |

---

## Conclusión

El Teorema Maestro permite resolver recurrencias de divide y vencerás comparando el costo de las llamadas recursivas ($n^{\log_b a}$) con el trabajo local $f(n)$:

- Si las llamadas dominan → Caso 1.
- Si hay equilibrio → Caso 2.
- Si el trabajo local domina → Caso 3 (con verificación de regularidad).

Las cuatro recurrencias resueltas cubren los tres casos posibles del teorema, lo que permite contrastar el comportamiento asintótico de distintos esquemas algorítmicos.