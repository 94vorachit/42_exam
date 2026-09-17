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
// #include <stdlib.h>
#include <math.h> //sqrtf
#include <float.h> //FLT_MAX

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
    
    // Distances between consecutive cities
    for (i = 0; i < n - 1; i++)
    {
        total += calculate_distance(cities[path[i]], cities[path[i + 1]]);
    }
    
    // Distance back to the start (closing the loop)
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

    // Generate all permutations by swapping elements
    for (int i = pos; i < n; i++)
    {
        swap(&path[pos], &path[i]); // Swap
        find_shortest_path(cities, path, n, pos + 1, min_distance); // Retake the course
        swap(&path[pos], &path[i]); // Restore (backtrack)
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
    
    City cities[12];  // Maximum 11 cities + margin
    int n = 0;
    
    // Read coordinates from stdin
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
    
    // Initialize path: [0, 1, 2, ..., n-1]
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
* COMPLEXITY AND OPTIMIZATIONS:
*
* 1. TIME COMPLEXITY:
*    - Brute force: O(n!)
*    - With optimization: O((n-1)!)
*    - For n=11: ~3.6 million permutations
*
* 2. ADDITIONAL OPTIMIZATIONS:
*    - Dynamic programming with bitmasks: O(n²2ⁿ)
*    - Christofides algorithm: 1.5x optimal approximation
*    - Heuristics: nearest neighbor, 2-opt, etc.
*
* 3. EARLY PRUNING:
*    - If partial distance > current_min, prune branch
*    - Use lower bound (MST) for aggressive pruning
*
* 4. NUMERICAL PRECISION:
*    - Use float for efficiency
*    - Watch out for rounding errors in comparisons
*/

/*
 * ALTERNATIVE IMPLEMENTATION WITH PRUNING:
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
* KEY POINTS FOR THE EXAM:
*
* 1. READING INPUT:
*    - Format: "x, y" per line
*    - Use fscanf(stdin, "%f, %f", &x, &y)
*    - Read until EOF or a maximum of 11 cities
*
* 2. EUCLIDEAN DISTANCE:
*    - Formula: sqrt((x2-x1)² + (y2-y1)²)
*    - Use sqrtf() for floats
*    - Compile with -lm
*
* 3. HAMILTONIAN CYCLE:
*    - CRUCIAL: add the distance back to the start
*    - Without this, the problem would be "shortest path," not TSP
*
* 4. PERMUTATION OPTIMIZATION:
*    - Fixing the first city reduces the factorial complexity
*    - Essential for the algorithm to finish in a reasonable time
*
* 5. SPECIAL CASES:
*    - 0 or 1 cities: distance 0.00
*    - 2 cities: 2 × distance between them
*    - Invalid input: handle gracefully
*/

/*
* จุดสำคัญสำหรับการสอบ:
*
* 1. การอ่านข้อมูลเข้า:
* - รูปแบบ: "x, y" ต่อบรรทัด
* - ใช้ fscanf(stdin, "%f, %f", &x, &y)
* - อ่านจนถึง EOF หรือสูงสุด 11 เมือง
*
* 2. ระยะทางแบบยูคลิด:
* - สูตร: sqrt((x2-x1)² + (y2-y1)²)
* - ใช้ sqrtf() สำหรับเลขทศนิยม
* - คอมไพล์ด้วย -lm
*
* 3. วงจรแฮมิลโทเนียน:
* - สำคัญมาก: เพิ่มระยะทางกลับไปยังจุดเริ่มต้น
* - หากไม่มีสิ่งนี้ ปัญหาจะเป็น "เส้นทางที่สั้นที่สุด" ไม่ใช่ TSP
*
* 4. การเพิ่มประสิทธิภาพด้วยการเรียงลำดับ:
* - การกำหนดเมืองแรกให้คงที่ช่วยลดแฟกทอเรียล
* - จำเป็นสำหรับ อัลกอริทึมเพื่อให้เสร็จสิ้นภายในเวลาที่เหมาะสม
*
* 5. กรณีพิเศษ:
* - 0 หรือ 1 เมือง: ระยะทาง 0.00
* - 2 เมือง: 2 เท่าของระยะทางระหว่างเมือง
* - ข้อมูลไม่ถูกต้อง: จัดการอย่างเหมาะสม
*/