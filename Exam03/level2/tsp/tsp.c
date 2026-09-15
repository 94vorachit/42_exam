/*
 * EXERCISE: TSP (Traveling Salesman Problem)
 *
 * DESCRIPTION:
 * Find the shortest route that visits every city exactly once
 * and returns to the starting point (a Hamiltonian cycle).
 *
 * KEY CONCEPTS:
 * 1. NP-COMPLETE PROBLEM: No known polynomial-time solution
 * 2. BRUTE FORCE: Feasible for ≤11 cities (11! permutations)
 * 3. EUCLIDEAN DISTANCE: sqrt((x2-x1)² + (y2-y1)²)
 * 4. PERMUTATIONS: Generate all possible visit orders
 * 5. OPTIMIZATION: Fix the first city to reduce computation
 *
 * ALGORITHM:
 * 1. Read city coordinates from stdin
 * 2. Generate all permutations of cities
 * 3. Compute total distance for each permutation (including return)
 * 4. Find the permutation with the smallest distance
 * 5. Print result with 2 decimal places
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Structure to represent a city
typedef struct {
    float x, y;
} City;

// Calculate Euclidean distance between two cities
float calculate_distance(City a, City b)
{
    /*
     * EUCLIDEAN DISTANCE:
     * d = √[(x2-x1)² + (y2-y1)²]
     *
     * Use sqrtf() for better performance with floats
     * Remember to compile with -lm to link the math library
     */
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

// Compute total distance of a complete route
float calculate_total_distance(City *cities, int *path, int n)
{
    /*
     * TOTAL CYCLE DISTANCE:
     * - Sum distances between consecutive cities in the path
     * - IMPORTANT: Add return distance (last → first)
     *   to complete the Hamiltonian cycle
     */
    float total = 0.0f;
    int i;
    
    // Distancias entre ciudades consecutivas
    for (i = 0; i < n - 1; i++)
    {
        total += calculate_distance(cities[path[i]], cities[path[i + 1]]);
    }
    
    // Distancia de vuelta al inicio (cerrar el ciclo)
    total += calculate_distance(cities[path[n - 1]], cities[path[0]]);
    
    /*
     * COMPLEXITY AND OPTIMIZATIONS:
     *
     * 1. TIME COMPLEXITY:
     *    - Brute force: O(n!)
     *    - With optimization: O((n-1)!)
     *    - For n=11: ~3.6 million permutations
     *
     * 2. ADDITIONAL OPTIMIZATIONS:
     *    - Dynamic programming with bitmasks: O(n^2 2^n)
     *    - Christofides algorithm: 1.5x optimal approximation
     *    - Heuristics: nearest neighbor, 2-opt, etc.
     *
     * 3. EARLY PRUNING:
     *    - If partial distance > current_min, prune branch
     *    - Use lower bounds (MST) for aggressive pruning
     *
     * 4. NUMERICAL PRECISION:
     *    - Use float for performance
     *    - Take care with rounding errors in comparisons
     *
     * ALTERNATIVE IMPLEMENTATION WITH PRUNING:
     *
     * void find_shortest_with_pruning(City *cities, int *path, int n, int pos,
     *                                 float current_dist, float *min_dist)
     * {
     *     // Pruning: if current distance already exceeds minimum
     *     if (current_dist >= *min_dist)
     *         return;
     *
     *     if (pos == n)
     *     {
     *         // Add return distance
     *         float total = current_dist + calculate_distance(cities[path[n-1]], cities[path[0]]);
     *         if (total < *min_dist)
     *             *min_dist = total;
     *         return;
     *     }
     */
    
    return total;
}

// swap two integers (indices in the path)
static void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Recursive permutation generator to find the shortest Hamiltonian cycle
void find_shortest_path(City *cities, int *path, int n, int pos, float *min_distance)
{
    if (pos == n)
    {
        float total = calculate_total_distance(cities, path, n);
        if (total < *min_distance)
            *min_distance = total;
        return;
    }

    for (int i = pos; i < n; i++)
    {
        swap(&path[pos], &path[i]);
        find_shortest_path(cities, path, n, pos + 1, min_distance);
        swap(&path[pos], &path[i]);
    }
}

int main(void)
{
    /*
     * MAIN PROCESSING:
     * 1. Read coordinates from stdin until EOF
     * 2. Validate minimum number of cities
     * 3. Initialize path and minimum distance
     * 4. Apply optimization: fix the first city
     * 5. Find the shortest path
     * 6. Print the result
     */
    
    City cities[12];  // Máximo 11 ciudades + margen
    int n = 0;
    
    // Leer coordenadas desde stdin
    while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
    {
        n++;
    }
    
    // Special cases
    if (n < 2)
    {
        printf("0.00\n");
        return 0;
    }
    
    // Inicializar path: [0, 1, 2, ..., n-1]
    int path[12];
    for (int i = 0; i < n; i++)
    {
        path[i] = i;
    }
    
    float min_distance = FLT_MAX;
    
    /*
     * CRUCIAL OPTIMIZATION:
     *
     * Since we are looking for a CYCLE, all circular rotations
     * yield the same total distance:
     * [0,1,2,3] ≡ [1,2,3,0] ≡ [2,3,0,1] ≡ [3,0,1,2]
     *
     * Therefore, we can FIX the first city at position 0
     * and only permute the rest. This reduces complexity from
     * n! to (n-1)!, a significant improvement.
     *
     * For 11 cities: from 39,916,800 to 3,628,800 permutations
     */
    
    // Generate permutations only for cities 1..n-1
    // (keeping city 0 fixed in the first position)
    find_shortest_path(cities, path, n, 1, &min_distance);
    
    // Print result with 2 decimals
    printf("%.2f\n", min_distance);
    
    return 0;
}

/*
 * EXAMPLE RUN:
 *
 * Input:
 * 0, 0
 * 1, 0
 * 1, 1
 * 0, 1
 *
 * Cities:
 * (0,0) → (1,0) → (1,1) → (0,1) → return to (0,0)
 *
 * Distances:
 * (0,0)→(1,0): 1.00
 * (1,0)→(1,1): 1.00
 * (1,1)→(0,1): 1.00
 * (0,1)→(0,0): 1.00
 * Total: 4.00
 *
 * Output: 4.00
 */

/*
 * COMPLEJIDAD Y OPTIMIZACIONES:
 * 
 * 1. COMPLEJIDAD TEMPORAL:
 *    - Fuerza bruta: O(n!)
 *    - Con optimización: O((n-1)!)
 *    - Para n=11: ~3.6 millones de permutaciones
 * 
 * 2. OPTIMIZACIONES ADICIONALES:
 *    - Programación dinámica con bitmasks: O(n²2ⁿ)
 *    - Algoritmo de Christofides: aproximación 1.5x óptimo
 *    - Heurísticas: nearest neighbor, 2-opt, etc.
 * 
 * 3. PODA TEMPRANA:
 *    - Si distancia parcial > min_actual, podar rama
 *    - Usar cota inferior (MST) para poda agresiva
 * 
 * 4. PRECISIÓN NUMÉRICA:
 *    - Usar float para eficiencia
 *    - Cuidar errores de redondeo en comparaciones
 */

/*
 * IMPLEMENTACIÓN ALTERNATIVA CON PODA:
 * 
 * void find_shortest_with_pruning(City *cities, int *path, int n, int pos, 
 *                                 float current_dist, float *min_dist)
 * {
 *     // Poda: si distancia actual ya supera el mínimo
 *     if (current_dist >= *min_dist)
 *         return;
 *     
 *     if (pos == n)
 *     {
 *         // Agregar distancia de vuelta
 *         float total = current_dist + calculate_distance(cities[path[n-1]], cities[path[0]]);
 *         if (total < *min_dist)
 *             *min_dist = total;
 *         return;
 *     }
 *     
 *     for (int i = pos; i < n; i++)
 *     {
 *         swap(&path[pos], &path[i]);
 *         
 *         float next_dist = current_dist;
 *         if (pos > 0)
 *             next_dist += calculate_distance(cities[path[pos-1]], cities[path[pos]]);
 *         
 *         find_shortest_with_pruning(cities, path, n, pos + 1, next_dist, min_dist);
 *         
 *         swap(&path[pos], &path[i]);
 *     }
 * }
 */

/*
 * PUNTOS CLAVE PARA EL EXAMEN:
 * 
 * 1. LECTURA DE ENTRADA:
 *    - Formato: "x, y" por línea
 *    - Usar fscanf(stdin, "%f, %f", &x, &y)
 *    - Leer hasta EOF o máximo 11 ciudades
 * 
 * 2. DISTANCIA EUCLIDIANA:
 *    - Fórmula: sqrt((x2-x1)² + (y2-y1)²)
 *    - Usar sqrtf() para floats
 *    - Compilar con -lm
 * 
 * 3. CICLO HAMILTONIANO:
 *    - CRUCIAL: agregar distancia de vuelta al inicio
 *    - Sin esto, el problema sería "shortest path" no TSP
 * 
 * 4. OPTIMIZACIÓN DE PERMUTACIONES:
 *    - Fijar primera ciudad reduce factorial
 *    - Fundamental para que el algoritmo termine en tiempo razonable
 * 
 * 5. CASOS ESPECIALES:
 *    - 0 o 1 ciudades: distancia 0.00
 *    - 2 ciudades: 2 × distancia entre ellas
 *    - Entrada inválida: manejar graciosamente
 */