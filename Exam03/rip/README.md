EXERCISE: RIP

DESCRIPTION:
* Given an unbalanced parenthesis string, remove the minimum number of parentheses to make the expression balanced. Print all possible solutions.

KEY CONCEPTS:

	1. PARENTHESIS VALIDATION: Classic counter-based algorithm
	2. BACKTRACKING: Explore all removal combinations
	3. OPTIMIZATION: First find the minimum number of removals
	4. GENERATION: Produce all solutions with the minimum found

ALGORITHM:

	1. Find the minimum number of parentheses to remove
	2. Generate all combinations by removing exactly that amount
	3. Check which ones result in balanced expressions
	4. Print all valid solutions

EXAMPLE EXECUTION:

./rip '(()'

PROCESS:
1. Original string: "(()"
2. Check if it is balanced: NO (final balance = 1)
3. Find the minimum:
   - Remove first '(': "())" → balance = -1 → INVALID
   - Remove second '(': "())" → balance = -1 → INVALID
   - Remove ')': "((" → balance = 2 → INVALID
   - Remove first '(' and ')': " ()" → balance = 0 → VALID (1 removal)
   - Remove second '(' and ')': "( )" → balance = 0 → VALID (1 removal)
4. Minimum = 1
5. Generate solutions with 1 removal:
   - " ()" → Print
   - "( )" → Print
```c
Output:
  ()
( )
```

OPTIMIZED ALGORITHM (for complex cases):

```c
void rip_optimized(char *str)
{
    // Count unbalanced parentheses
    int open = 0, close = 0;

    // First pass: count excess ')'
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')' && open > 0)
            open--;
        else if (str[i] == ')')
            close++;  // ')' without a matching '('
    }

    // open = excess '(', close = excess ')'
    // Total to remove = open + close

    generate_solutions_optimized(str, 0, 0, open, close);
}
```

SPECIAL CASES:

1. Already balanced string: "()" → Remove nothing
2. Only opening parentheses: "(((" → Remove all
3. Only closing parentheses: ")))" → Remove all
4. Empty string: "" → Already balanced
5. Single parenthesis: "(" or ")" → Remove the only one

KEY POINTS FOR THE EXAM:

1. PARENTHESES VALIDATION:
   - Classic counter-based algorithm
   - balance++ for '(', balance-- for ')'
   - balance < 0 at any moment = invalid
   - balance == 0 at the end = valid

2. BACKTRACKING IN TWO PHASES:
   - Phase 1: Find the minimum number of removals
   - Phase 2: Generate all solutions with that minimum
   - Use the same recursive structure for both

3. REMOVAL REPRESENTATION:
   - Replace with space ' ' instead of deleting
   - Easier than handling variable-length strings
   - Restore the original character after each attempt

4. EFFICIENT PRUNING:
   - Stop if current_removals > min_removals
   - Avoid exploring unnecessary branches
   - Crucial for performance on long strings

5. MULTIPLE SOLUTIONS:
   - There may be several ways to remove the minimum
   - Generate all of them systematically
   - Do not allow duplicates (the exploration order matters)

STEP BY STEP

1. initiate  `int main(int ac, char **av)` and chech error from args
	
	VALIDATION AND PROCESSING:
	* Verify valid arguments
	* Validate that it only contains parentheses
	* Find the minimum number of removals
	* Generate all solutions with that minimum
	```c
	int	main(int ac, char **av)
	{
		if (ac != 2 || av[1][0] == '\0')
			return (1);
		int	i = 0;
		while (av[1][i])
		{
			if (av[1][i] != '(' && av[1][i] != ')')
				return (1);
			i++;
		}
	}
	```

2. initiate `int min_removals = ft_strlen(av[1])`

	```c
	#include <unistd.h>

	int	ft_strlen(char *s)
	{
		int	i = 0;
		while (s[i])
			i++;
		return (i);
	}
	```
	```c
	int	main(int ac, char **av)
	{
		...
		int	min_removals = ft_strlen(av[1]);
		...
	}
	```
3. initiate function to check if a string is balanced

	PARENTHESES VALIDATION ALGORITHM:
	* Use a counter for open parentheses
	* Increment by '(', decrement by ')'
	* If the counter is less than 0 at any time: unbalanced
	* The counter must be 0 at the end
	```c
	int	ft_is_balanced(char *str, int len)
	{
		int	balance = 0;
		int i = 0;

		while (i < len)
		{
			if (str[i] == '(')
				balance++;
			else if (str[i] == ')')
			{
				balance--;
				if (balance < 0) // More ')' than '(' so far
					return (0);
			}
			// Ignore spaces (removed characters)
			i++;
		}
		return (balance == 0); // Balanced if final counter is 0
	}
	```
4. Initiate Function to find the minimum number of removals needed

	MINIMUM SEARCH:
	* Try removing each set of parentheses one by one
	* If the resulting string is balanced, update minimum
	* Use backtracking to explore all combinations
	* Prune if current_removals is already greater than the known minimum

	```c
	void ft_find_min_removals(char *str, int *min_removals, int index, int current_removals)
	{
		// Pruning: if we have already removed more than the known minimum, do not continue
		if (current_removals > *min_removals)
			return ;

		// Check if the current chain is balanced
		if (ft_is_balanced(str, ft_strlen(str)))
		{
			if (current_removals < *min_removals)
				*min_removals = current_removals;
			return ;
		}

		// Try removing each parenthesis from the index position
		int	i = index;
		while (str[i])
		{
			// Only try to remove parentheses, not spaces
			if (str[i] == '(' || str[i] == ')')
			{
				char	saved = str[i];
				str[i] = ' '; // "Remove" by replacing with a space
				ft_find_min_removals(str, min_removals, i + 1, current_removals + 1);
				str[i] = saved; // Restore to try other options
			}
			i++;
		}
	}
	```
	```c
	int	main(int ac, char **av)
	{
		...
		// Find the minimum number of removals needed
		ft_find_min_removals(av[1], &min_removals, 0, 0);
		...
	}
	```

5. Initiate function to generate all valid solutions

	SOLUTION GENERATION:
	* Only explore combinations that remove exactly min_removals
	* Check if each combination is balanced
	* Print the balanced ones
	* Use backtracking to explore systematically

	```c
	void	ft_generate_solutions(char *str, int min_removals, int index, int current_removals)
	{
		// Pruning: if we have already removed more than the minimum, do not continue
		if (current_removals > min_removals)
			return ;

		// If we removed exactly the minimum, check if it is balanced
		if (ft_is_balanced(str, ft_strlen(str)) && current_removals == min_removals)
		{
			// Print valid solution
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
			return ;
		}

		// Try removing each parenthesis from the index position
		int	i = index;
		while (str[i])
		{
			// Just try to remove parentheses, not spaces
			if (str[i] == '(' || str[i] == ')')
			{
				char saved = str[i];
				str[i] = ' '; // "Remove" by replacing with a space
				ft_generate_solutions(str, min_removals, i+ 1, current_removals + 1);
				str[i] = saved; // Restore to try other options
			}
			i++;
		}
	}
	```
	```c
	int	main(int ac, char **av)
	{
		...
		// Generate all solutions with the minimum number of removals
		ft_generate_solutions(argv[1], min_removals, 0, 0);
		...
	}
	```
