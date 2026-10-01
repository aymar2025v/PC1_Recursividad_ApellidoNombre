# Actividad 1: Traza de la pila de llamadas — `suma_digitos(12345)`

**Curso:** Algoritmos y Estructuras de Datos — SIS210  
**Práctica:** PC1 — Recursividad, Recurrencias y Divide y Vencerás  
**Estudiante:** [Apellido Nombre]  
**Fecha:** [Fecha]

---

## 1. Código analizado

```python
def suma_digitos(n: int) -> int:
    if n < 10:
        return n
    return n % 10 + suma_digitos(n // 10)
```

## 2. Traza manual de la pila de llamadas

Llamada inicial: `suma_digitos(12345)`

| N.º | Llamada | `n` | `n % 10` (dígito) | `n // 10` | Retorna |
|-----|---------|----:|------------------:|----------:|---------|
| 1 | `suma_digitos(12345)` | 12345 | 5 | 1234 | `5 + suma_digitos(1234)` |
| 2 | `suma_digitos(1234)`  | 1234  | 4 | 123  | `4 + suma_digitos(123)`  |
| 3 | `suma_digitos(123)`   | 123   | 3 | 12   | `3 + suma_digitos(12)`   |
| 4 | `suma_digitos(12)`    | 12    | 2 | 1    | `2 + suma_digitos(1)`    |
| 5 | `suma_digitos(1)`     | 1     | 1 | 0    | **`1`** ← caso base     |

## 3. Desenrollado de la pila (retorno)

Una vez alcanzado el caso base, la pila se desenrolla de arriba hacia abajo:

```text
suma_digitos(1)     = 1
suma_digitos(12)    = 2 + 1  = 3
suma_digitos(123)   = 3 + 3  = 6
suma_digitos(1234)  = 4 + 6  = 10
suma_digitos(12345) = 5 + 10 = 15
```

## 4. Representación gráfica de la pila

```text
        ┌─────────────────────────────┐
        │  suma_digitos(12345)        │  ← tope (llamada más reciente)
        ├─────────────────────────────┤
        │  suma_digitos(1234)         │
        ├─────────────────────────────┤
        │  suma_digitos(123)          │
        ├─────────────────────────────┤
        │  suma_digitos(12)           │
        ├─────────────────────────────┤
        │  suma_digitos(1)  ← base    │
        └─────────────────────────────┘
                ↓ desenrollado ↓
        Resultado final: 15
```

## 5. Propiedades observadas

| Propiedad | Valor |
|-----------|-------|
| Profundidad máxima de recursión | 5 (número de dígitos) |
| Número total de llamadas | 5 |
| Costo de memoria | $O(d)$ donde $d$ = número de dígitos |
| Costo temporal | $O(d)$ |
| Relación con $n$ | $d = \lfloor \log_{10} n \rfloor + 1$ |
| Complejidad asintótica | $T(n) = \Theta(\log_{10} n)$ |

## 6. Verificación en C++

```cpp
int sumaDigitos(int n) {
    if (n < 10) return n;
    return n % 10 + sumaDigitos(n / 10);
}
```

La traza es idéntica. La única diferencia es el tipo `int` y el uso de `/` en lugar de `//`.

## 7. Conclusión

La traza confirma que:

- El caso base se alcanza cuando `n` tiene un solo dígito (`n < 10`).
- El caso recursivo reduce el problema a `n // 10`, estrictamente menor que `n`.
- La profundidad de la pila es proporcional al número de dígitos, no al valor de `n`.
- La suma total es `5 + 4 + 3 + 2 + 1 = 15`, verificando el `assert`.