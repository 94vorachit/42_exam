EXERCISE: PERMUTATIONS

DESCRIPTION:
Generate all permutations of a given string in alphabetical order.

KEY CONCEPTS:
1. BACKTRACKING: Exhaustive search algorithm
2. SORTING: Ensure alphabetical order
3. RECURSION: Generate permutations level by level
4. STATE: Track which characters have already been used

ALGORITHM:
1. Sort the original string alphabetically
2. For each position, try every unused character
3. Mark the character as used and recurse
4. Unmark the character when returning (backtrack)
5. Print when a permutation is complete

 KEY POINTS FOR THE EXAM:
1. ALPHABETICAL ORDER:
	- It is CRUCIAL to sort the string before generating permutations
	- Without sorting, alphabetical order is not guaranteed
	- Use a simple but correct sorting algorithm
2. EFFICIENT BACKTRACKING:
	- Use an array of used characters for O(n) checking
	- Mark and unmark characters correctly
	- Do not forget to clear the state when returning 
3. MEMORY MANAGEMENT:
	- Allocate a buffer for the current permutation
	- Use calloc() to initialize it to '\0'
	- Free memory when finished 
4. ROBUST VALIDATION:
	- Check the number of arguments
	- Validate that it contains only letters
	- Handle special cases (empty string, spaces)
5. OPTIMIZATIONS:
	- For strings with duplicate characters, use a different algorithm
	- For very long strings, consider Heap's algorithm
	- Avoid regenerating duplicate permutations

STEP BY STEP

1. Make `int main(int ac, char **av)` :

	VALIDATION AND PROCESSING:
	 - Check valid arguments
	 - Validate it contains only letters
	 - Sort string alphabetically
	 - Initialize result buffer
	 - Generate all permutations

	```c
	#include <unistd.h> // write
	#include <stdlib.h> // calloc

	// Helper function to calculate length
	int ft_strlen(char *s)
	{
    	int i = 0;
    	while (s[i])
        	i++;
    	return i;
	}

	// Helper function to check if character is alphabetic
	int ft_isalpha(int c)
	{
    	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
	}

	int main(int ac, char **av)
	{
		if (ac != 2)
			return (1);
		
		// Check empty string or single-space
		if (ft_strlen(av[1] == 0 || (av[1][0] == ' ' && !av[1][1])))
			return (0);

		// Validate it contains only alphabetic characters
		int	i = 0;
		while (av[1][i])
		{
			if (!ft_isalpha(av[1][i]))
				return (0);
			i++;
		}

		int	len = ft_strlen(av[1]);

		// Allocate buffer for the result (current permutation)
		char	*result = calloc(len + 1, 1);
		if (!result)
			return (1);
	}
	```

2. Make sort string alphabetically (bubble sort) function :

    BUBBLE SORT:
     - Compare adjacent characters
     - Swap if they are in the wrong order
     - Repeat until no swaps occur
     - Guarantees alphabetical order for permutations

	```c
	// Swap two characters
	void ft_swap(char *a, char *b)
	{
    	char temp = *a;
    	*a = *b;
    	*b = temp;
	}

	// Sort string alphabetically (bubble sort)
	char *ft_order_string(char *s)
	{
		int len = ft_strlen(s);
		int swapped = 1;
		
		while (swapped)
		{
			swapped = 0;
			int i = 0;
			while (i < len - 1)
			{
				if (s[i] > s[i + 1])
				{
					ft_swap(&s[i], &s[i + 1]);
					swapped = 1;
				}
				i++;
			}
		}
		return (s);
	}

	int main(int ac, char **av)
	{
		...
		// Sort the string alphabetically
    	char *source = order_string(av[1]);
	}
	```

3. Make recursive function to generate permutations

    BACKTRACKING ALGORITHM FOR PERMUTATIONS:
    
	BASE CASE: If pos == length, we have a complete permutation
     - Print the current permutation
     - Return to try other options
    RECURSIVE CASE: For each character in source:
     - If it's not used in result, try it
     - Place it at result[pos]
     - Recurse for the next position
     - Remove character (backtrack) to try others

	```c
	// Check if character is already used (exists in string)
	int ft_strchr(const char *s, char c)
	{
		int i = 0;
		while (s[i])
		{
			if (s[i] == c)
				return 1; // Encontrado
			i++;
		}
		return 0; // No encontrado
	}

	// Recursive function to generate permutations
	void generate_permutations(char *source, char *result, int pos)
	{
		int source_len = ft_strlen(source);
		
		// Base case: complete permutation
		if (pos == source_len)
		{
			write(1, result, source_len);
			write(1, "\n", 1);
			return;
		}
		
		// Try every character in source
		int i = 0;
		while (i < source_len)
		{
			// Check if the character is already used
			if (!ft_strchr(result, source[i]))
			{
				result[pos] = source[i];        // Use character
				generate_permutations(source, result, pos + 1);  // Recurse
				result[pos] = '\0';             // Backtrack: remove character
			}
			i++;
		}
	}

	int	main(int ac, char **av)
	{
		...
		// Generate all permutations
    	generate_permutations(source, result, 0);
		free(result);
		return (0);
	}
	```