# EXERCISE: TSP (Traveling Salesman Problem)

DESCRIPTION:
Find the shortest route that visits every city exactly once
and returns to the starting point (a Hamiltonian cycle).

KEY CONCEPTS:
1. NP-COMPLETE PROBLEM: No known polynomial-time solution
2. BRUTE FORCE: Feasible for ≤11 cities (11! permutations)
3. EUCLIDEAN DISTANCE: sqrt((x2-x1)² + (y2-y1)²)
4. PERMUTATIONS: Generate all possible visit orders
5. OPTIMIZATION: Fix the first city to reduce computation

ALGORITHM:
1. Read city coordinates from stdin
2. Generate all permutations of cities
3. Compute total distance for each permutation (including return)
4. Find the permutation with the smallest distance
5. Print result with 2 decimal places

# EXAMPLE RUN:

Input:
0, 0
1, 0
1, 1
0, 1

Cities:
(0,0) → (1,0) → (1,1) → (0,1) → return to (0,0)

Distances:
(0,0)→(1,0): 1.00
(1,0)→(1,1): 1.00
(1,1)→(0,1): 1.00
(0,1)→(0,0): 1.00
Total: 4.00

Output: 4.00

# COMPLEXITY AND OPTIMIZATIONS:

1. TIME COMPLEXITY:
   - Brute force: O(n!)
   - With optimization: O((n-1)!)
   - For n=11: ~3.6 million permutations

2. ADDITIONAL OPTIMIZATIONS:
   - Dynamic programming with bitmasks: O(n²2ⁿ)
   - Christofides algorithm: 1.5x optimal approximation
   - Heuristics: nearest neighbor, 2-opt, etc.

3. EARLY PRUNING:
   - If partial distance > current_min, prune branch
   - Use lower bound (MST) for aggressive pruning

4. NUMERICAL PRECISION:
   - Use float for efficiency
   - Watch out for rounding errors in comparisons

# KEY POINTS FOR THE EXAM:

1. READING INPUT:
   - Format: "x, y" per line
   - Use fscanf(stdin, "%f, %f", &x, &y)
   - Read until EOF or a maximum of 11 cities

2. EUCLIDEAN DISTANCE:
   - Formula: sqrt((x2-x1)² + (y2-y1)²)
   - Use sqrtf() for floats
   - Compile with -lm

3. HAMILTONIAN CYCLE:
   - CRUCIAL: add the distance back to the start
   - Without this, the problem would be "shortest path," not TSP

4. PERMUTATION OPTIMIZATION:
   - Fixing the first city reduces the factorial complexity
   - Essential for the algorithm to finish in a reasonable time

5. SPECIAL CASES:
   - 0 or 1 cities: distance 0.00
   - 2 cities: 2 × distance between them
   - Invalid input: handle gracefully

# STEP BY STEP

1. Given codes
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct s_city
{
	float x;
	float y;
}	t_city;

/*
** You must implement this function
** It should return the Euclidean distance between 2 cities
*/
float	distance(t_city a, t_city b);

/*
** You must implement this function
** It should compute total distance of the path
** including the return to the starting city
*/
float	total_distance(t_city *cities, int *path, int n);

/*
** You must implement this function
** Use backtracking to try all permutations
*/
void	solve(t_city *cities, int *path, int n, int pos, float *min);

int	main(void)
{
	t_city	cities[11];
	int		n = 0;

	// Read input from stdin
	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;

	// If less than 2 cities → distance = 0
	if (n < 2)
	{
		printf("0.00\n");
		return (0);
	}

	// Initialize path: [0,1,2,...]
	int path[11];
	for (int i = 0; i < n; i++)
		path[i] = i;

	float min = FLT_MAX;

	/*
	** Optimization:
	** Fix first city → start from pos = 1
	*/
	solve(cities, path, n, 1, &min);

	printf("%.2f\n", min);
	return (0);
}
```

2. Write distance function
```c
float	distance(t_city a, t_city b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return (sqrtf(dx * dx + dy * dy));
}
```

3. Write total_distance function
```c
float	total_distance(t_city *cities, int *path, int n)
{
	float total = 0.0f;
	int	i;

	for (i = 0; i < n - 1; i++)
		total += distance(cities[path[i]], cities[path[i + 1]]);
	total += distance(cities[path[n - 1]], cities[path[0]]);
	return (total); 
}
```

4. Add ft_swap function
```c
void ft_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

5. Write solve function
```c
void	solve(t_city *cities, int *path, int n, int pos, float *min)
{
	if (pos == n)
	{
		float total = total_distance(cities, path, n);
		if (total < *min)
			*min = total;
		return ;
	}

	for (int i = pos; i < n; i++)
	{
		swap(&path[pos], &path[i]);
		slove(cities, path, n, pos + 1, min);
		swap(&path[pos], &path[i]);
	}
}
```