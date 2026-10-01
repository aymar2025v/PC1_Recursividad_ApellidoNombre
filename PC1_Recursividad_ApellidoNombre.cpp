#include <iostream> //
#include <cassert>
#include <vector> //
#include <utility>
#include <cmath> //
#include <chrono> //
#include <random> 
#include <algorithm> //
#include <numeric>
#include <fstream> // std::ofstream
#include <iomanip> // std::setprecision
#include <string>  // std::string

// ============================================================
// ACTIVIDAD 1: Suma de dígitos recursiva
// ============================================================

int sumaDigitos(int n)
{
    if (n < 10)
        return n;
    return n % 10 + sumaDigitos(n / 10);
}

// ============================================================
// ACTIVIDAD 2: Búsqueda Binaria con conteo de comparaciones
// ============================================================

std::pair<int, int> busquedaBinaria(const std::vector<int> &arr, int obj)
{
    int bajo = 0;
    int alto = static_cast<int>(arr.size()) - 1;
    int comparaciones = 0;

    while (bajo <= alto)
    {
        comparaciones++;
        int medio = (bajo + alto) / 2;
        if (arr[medio] == obj)
            return {medio, comparaciones};
        else if (arr[medio] < obj)
            bajo = medio + 1;
        else
            alto = medio - 1;
    }
    return {-1, comparaciones};
}

// ============================================================
// ACTIVIDAD 3: Merge Sort
// ============================================================

std::vector<int> merge(const std::vector<int> &izq, const std::vector<int> &der)
{
    std::vector<int> res;
    res.reserve(izq.size() + der.size());
    size_t i = 0, j = 0;
    while (i < izq.size() && j < der.size())
    {
        if (izq[i] <= der[j])
            res.push_back(izq[i++]);
        else
            res.push_back(der[j++]);
    }
    while (i < izq.size())
        res.push_back(izq[i++]);
    while (j < der.size())
        res.push_back(der[j++]);
    return res;
}

std::vector<int> mergeSort(const std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return arr;
    size_t mid = arr.size() / 2;
    std::vector<int> izq(arr.begin(), arr.begin() + mid);
    std::vector<int> der(arr.begin() + mid, arr.end());
    return merge(mergeSort(izq), mergeSort(der));
}

// ============================================================
// Helper: máxima cantidad de comparaciones de búsqueda binaria
// para todos los objetivos posibles en [0, n-1].
// ============================================================

int maxComparacionesBinaria(int n)
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = i;

    int maxComp = 0;
    for (int objetivo = 0; objetivo < n; ++objetivo)
    {
        auto [_, comp] = busquedaBinaria(arr, objetivo);
        if (comp > maxComp)
            maxComp = comp;
    }
    return maxComp;
}

// ============================================================
// main
// ============================================================

int main()
{
    // ---------- Actividad 1 ----------
    assert(sumaDigitos(12345) == 15);
    assert(sumaDigitos(0) == 0);
    assert(sumaDigitos(9) == 9);

    std::cout << "=== ACTIVIDAD 1 ===\n";
    std::cout << "suma_digitos(12345) = " << sumaDigitos(12345) << '\n';
    std::cout << "suma_digitos(0)     = " << sumaDigitos(0) << '\n';
    std::cout << "suma_digitos(9)     = " << sumaDigitos(9) << '\n';

    // ---------- Actividad 2: tabla de comparaciones ----------
    std::cout << "\n--- Tabla de comparaciones ---\n";

    // std::vector<int> valores_n = {10, 100, 1'000, 10'000, 100'000, 1'000'000};

    std::vector<int> valores_n = {10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1'000, 2000,
        5000, 8000, 9000, 10000, 15000, 17000,  
         20000, 30'000, 40000, 50000, 60000, 70000, 80000, 90000, 100'000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 
         1'000'000};

    std::ofstream csv2("outputs/comparaciones_busqueda.csv");
    if (!csv2.is_open())
    {
        std::cerr << "ERROR: no se pudo abrir outputs/comparaciones_busqueda.csv\n";
        return 1;
    }
    csv2 << "n,lineal_max_comp,binaria_max_comp,cota_teorica,cumple_cota\n";

    for (int n : valores_n)
    {
        int linealMax = n; // peor caso de búsqueda lineal
        int binariaMax = maxComparacionesBinaria(n);
        int cota = static_cast<int>(std::ceil(std::log2(n + 1)));
        std::string cumple = (binariaMax <= cota) ? "Si" : "No";

        std::cout << "n=" << n
                  << "  lineal=" << linealMax
                  << "  binaria=" << binariaMax
                  << "  cota=" << cota
                  << "  cumple=" << cumple << '\n';

        csv2 << n << ','
             << linealMax << ','
             << binariaMax << ','
             << cota << ','
             << cumple << '\n';
    }

    csv2.close();
    std::cout << "CSV guardado en outputs/comparaciones_busqueda.csv\n";

    // ---------- Actividad 3 ----------
    std::cout << "\n=== ACTIVIDAD 3 ===\n";

    // Prueba con códigos de matrícula simulados
    std::vector<int> codigos = {
        20211200, 20210300, 20211050, 20210780, 20211500,
        20210100, 20211800, 20210640, 20210950, 20211400};

    auto t0 = std::chrono::high_resolution_clock::now();
    std::vector<int> ordenados = mergeSort(codigos);
    auto t1 = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    std::cout << "Ordenados: ";
    for (int c : ordenados)
        std::cout << c << ' ';
    std::cout << '\n';

    // Verificación contra std::sort
    std::vector<int> esperado = codigos;
    std::sort(esperado.begin(), esperado.end());
    assert(ordenados == esperado);
    std::cout << "Verificacion OK contra std::sort\n";
    std::cout << "Tiempo (n=10): " << ms << " ms\n";

    // Benchmark para n grande
    std::cout << "\n--- Benchmark Merge Sort ---\n";

    std::mt19937 rng(42); // semilla fija para reproducibilidad
    std::uniform_int_distribution<int> dist(20'000'000, 29'999'999);

    std::vector<int> tamanios = {100, 1'000, 10'000, 100'000};

    // Abrir CSV
    std::ofstream csv("outputs/tiempos_benchmark.csv");
    if (!csv.is_open())
    {
        std::cerr << "ERROR: no se pudo abrir outputs/tiempos_benchmark.csv\n";
        std::cerr << "Crea la carpeta 'outputs' antes de ejecutar.\n";
        return 1;
    }

    // Encabezado del CSV
    csv << "n,tiempo_ms\n";

    for (int n : tamanios)
    {
        std::vector<int> datos(n);
        for (int &x : datos)
            x = dist(rng);

        auto a = std::chrono::high_resolution_clock::now();
        std::vector<int> res = mergeSort(datos);
        auto b = std::chrono::high_resolution_clock::now();

        double ms_n = std::chrono::duration<double, std::milli>(b - a).count();

        std::cout << "n=" << n
                  << "  tiempo=" << ms_n << " ms\n";

        // Escribir fila en CSV
        csv << n << ',' << std::fixed << std::setprecision(6) << ms_n << '\n';

        // Verificación rápida (solo para n moderado)
        if (n <= 10'000)
        {
            std::vector<int> check = datos;
            std::sort(check.begin(), check.end());
            assert(res == check);
        }
    }

    csv.close();
    std::cout << "\nCSV guardado en outputs/tiempos_benchmark.csv\n";

    std::cout << "\nFin del programa.\n";
    return 0;
}