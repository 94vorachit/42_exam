/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 02:09:17 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/04 04:44:42 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * EXERCISE: POWERSET
 *
 * DESCRIPTION:
 * Find all subsets of a set of integers whose sum is equal to a target.
 *
 * KEY CONCEPTS:
 * 1. BACKTRACKING: Explore all possible combinations
 * 2. SUBSET SUM: Classic subset-sum problem
 * 3. BINARY DECISION: For each element, include it or not
 * 4. ORDER PRESERVATION: Elements must keep their original order
 *
 * ALGORITHM:
 * 1. For each element, make two decisions: include it or not
 * 2. Keep the current sum and current subset
 * 3. If sum == target, print the subset
 * 4. Continue recursively with the remaining elements
 */

#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *subset, int size)
{
	/*
	 * OUTPUT FORMAT:
     * - If size == 0, print an empty line (empty subset)
     * - Print elements separated by spaces
     * - End with a newline
	 */
	if (size == 0)
	{
		printf("\n");
		return;
	}
	
	int	i = 0;
	while (i < size)
	{
		if (i == size - 1)
			printf("%d", subset[i]);
		else
			printf("%d ", subset[i]);
		i++;
	}
	printf("\n");
}

// Recursive backtracking function
void	backtrack(int *set, int *subset, int set_size, int subset_size, 
					int index, int current_sum, int target, int *found)
{
	/*
	 * PARAMETERS:
     * - set: Original array of numbers
     * - subset: Current array we are building
     * - set_size: Size of the original array
     * - subset_size: Current size of the subset
     * - index: Current position in the original array
     * - current_sum: Current sum of the subset
     * - target: Target sum
     * - found: Flag indicating whether a solution was found
     *
     * LOGIC:
     * At each call, we have two options:
     * 1. DO NOT include the current element (only advance the index)
     * 2. DO include the current element (add it to the subset and update the sum)
	 */

	// Base case: we have processed all elements
	if (index == set_size)
	{
		if (current_sum == target)
		{
			print_subset(subset, subset_size);
			*found = 1;
		}
		return; 
	}
	
	/*
	* DECISION 1: Do NOT include the current element
	* - We do not modify subset or current_sum
	* - We only advance to the next element
	*/
	backtrack(set, subset, set_size, subset_size, index + 1, current_sum, 
				target, found);

	/*
	* DECISION 2: YES, include the current element
	* - Add element to subset
	* - Update sum
	* - Increment subset size
	*/
	subset[subset_size] = set[index];
	backtrack(set, subset, set_size, subset_size + 1, index + 1, 
				current_sum + set[index], target, found);
	// Note: We don't need to explicitly "undo" because
	// subset[subset_size] will be overwritten on the next call
}

// Function to validate numeric arguments
int	check_args(int ac, char **av)
{
	/*
	 *ARGUMENT VALIDATION:
	 * - Verify that all arguments are valid numbers
	 * - Allow negative numbers (starting with '-')
	 * - Allow positive numbers (optionally with '+')
	 */
	int	i = 1;
	while (i < ac)
	{
		int	j = 0;
		// Skip initial sign if it exists
		if (av[i][j] == '+' || av[i][j] == '-')
			j++;
		// Verify that the rest are digits
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	/*
	 * SPECIAL CASES:
	 * - argc == 1: Only the program name
	 * - target == 0: An empty subset always sums to 0
	 * - Invalid arguments: Return an error
	 */
	
	if (ac < 2)
		return (1);
	// Special case: target = 0, print empty line and exit
	if (ac >= 2 && av[1][0] == '0' && av[1][1] == '\0')
	{
		printf("\n");
		return (0);
	}
	// else
	// 	printf("target = 0, print empty line and exit : check\n");

	// Validate arguments
	if (!check_args(ac, av))
	{
		// printf("Validate arguments : error\n");
		return (1);
	}
	// else
	// 	printf("Validate arguments : check\n");

	int	target = atoi(av[1]);
	int	set_size = ac - 2;

	if (set_size <= 0)
	{
		// printf("set size <= 0 : error\n");
		return (1);
	}
	// else
	// 	printf("set size <= 0 : check\n");

	// Allocate arrays for the current set and subset
	int	*set = malloc(sizeof(int) * set_size);
	int	*subset = malloc(sizeof(int) * set_size);
	
	if (!set || !subset)
	{
		free(set);
		free(subset);
		return (1);
	}

	// Fill the array with the numbers from the command
	int	i = 0;
	int	j = 2;
	while (j < ac)
	{
		set[i] = atoi(av[j]);
		i++;
		j++;
	}
	
	// int	n = 0;
	// while (n < i)
	// {
	// 	if (n == i - 1)
	// 		printf("%d", set[n]);
	// 	else
	// 		printf("%d ", set[n]);
	// 	n++;
	// }
	// printf("\n");

	int	found = 0;

	backtrack(set, subset, set_size, 0, 0, 0, target, &found);
	free(set);
	free(subset);
	return (0);
}

/*
 * ./powerset 3 1 0 2 4 5 3
 *
 * PROCESS:
 * - Target: 3
 * - Set: [1, 0, 2, 4, 5, 3]
 *
 * Subsets that sum to 3:
 * - [3] → sum = 3 ✓
 * - [0, 3] → sum = 3 ✓
 * - [1, 2] → sum = 3 ✓
 * - [1, 0, 2] → sum = 3 ✓
 *
 * Output:
 * 3
 * 0 3
 * 1 2
 * 1 0 2
 */

/*
 * DECISION TREE FOR [1, 0, 2] WITH TARGET 3:
 *
 *                    Root
 *                   /    \
 *            Do not include 1   Include 1
 *               /    \         /    \
 *        Do not inc 0   Inc 0   Do not inc 0   Inc 0
 *         /  \      /  \      /  \      /  \
 *    Do not inc 2  Inc 2  Do not inc 2  Inc 2  Do not inc 2  Inc 2
 *       |      |      |      |      |      |
 *    sum=0  sum=2  sum=0  sum=2  sum=1  sum=3 ✓
 *
 * Only the last case (Inc 1, Inc 0, Inc 2) sums to 3
 */

/*
 * POSSIBLE OPTIMIZATIONS:
 *
 * 1. EARLY PRUNING:
 *    - If current_sum > target and all remaining elements are positive, prune
 *    - If current_sum + sum_remaining < target, prune
 *
 * 2. SORTING:
 *    - Sorting the elements can improve pruning
 *    - But the original order must be preserved in the output
 *
 * 3. DYNAMIC PROGRAMMING:
 *    - For large sets, use DP
 *    - Table dp[i][sum] = whether it is possible to reach the sum with the first i elements
 */

/*
 * KEY POINTS FOR THE EXAM:
 *
 * 1. SUBSET SUM PROBLEM:
 *    - Classic NP-complete problem
 *    - Backtracking is the most direct exact solution
 *    - Worst-case complexity is O(2^n)
 *
 * 2. ELEMENT ORDER:
 *    - CRITICAL to keep the original order
 *    - Do not use permutations, only combinations
 *    - The subset [1,2] is different from [2,1] depending on the problem
 * 
 * 3. SPECIAL CASES:
 *    - Target = 0: The empty subset is always a solution
 *    - No elements: Only the empty subset is possible
 *    - Negative numbers: Allowed and must be handled correctly
 *
 * 4. MEMORY MANAGEMENT:
 *    - Dynamic arrays for the set and subset
 *    - Check malloc before using it
 *    - Free memory at the end
 *
 * 5. OUTPUT FORMAT:
 *    - Empty line for the empty subset
 *    - Spaces between numbers, not at the end
 *    - One line per subset found
 */