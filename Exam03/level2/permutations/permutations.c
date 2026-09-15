/*
 * EXERCISE: PERMUTATIONS
 * 
 * DESCRIPTION:
 * Generate all permutations of a given string in alphabetical order.
 * 
 * KEY CONCEPTS:
 * 1. BACKTRACKING: Exhaustive search algorithm
 * 2. SORTING: Ensure alphabetical order
 * 3. RECURSION: Generate permutations level by level
 * 4. STATE: Track which characters have already been used
 * 
 * ALGORITHM:
 * 1. Sort the original string alphabetically
 * 2. For each position, try every unused character
 * 3. Mark the character as used and recurse
 * 4. Unmark the character when returning (backtrack)
 * 5. Print when a permutation is complete
 */

#include <unistd.h>
#include <stdlib.h>
// #include <stdio.h>

// Helper function to calculate length
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

// Helper function to check whether a character is alphabetic
int ft_isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Function to swap two characters
void ft_swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Function to check whether a character is already in use
int ft_strchr(const char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1; // Found
        i++;
    }
    return 0; // Not found
}

// Function to sort a string alphabetically (bubble sort)
char *order_string(char *s)
{
    /*
    * BUBBLE SORT:
    * - Compare adjacent characters
    * - Swap them if they are in the wrong order
    * - Repeat until there are no swaps
    * - Guarantees alphabetical order for the permutations
     */
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
    return s;
}

// Recursive function to generate permutations
void generate_permutations(char *source, char *result, int pos)
{
    /*
    * BACKTRACKING ALGORITHM FOR PERMUTATIONS:
    * 
    * BASE CASE: If pos == length, we have a complete permutation
    * - Print the current permutation
    * - Return to try other options
    * 
    * RECURSIVE CASE: For each character in source:
    * - If it is not used in result, try it
    * - Add it to result[pos]
    * - Recurse for the next position
    * - Remove the character (backtrack) to try others
    */
    
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
        // Check whether the character is already used
        if (!ft_strchr(result, source[i]))
        {
            result[pos] = source[i];        // Use character
            generate_permutations(source, result, pos + 1);  // Recurse
            result[pos] = '\0';             // Backtrack: remove character
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    /*
    * VALIDATION AND PROCESSING:
    * - Check valid arguments
    * - Validate that it contains only letters
    * - Sort the string alphabetically
    * - Initialize the result buffer
    * - Generate all permutations
     */
    
    if (argc != 2)
        return 1;
    
    // Check for an empty string or a single space
    if (ft_strlen(argv[1]) == 0 || (argv[1][0] == ' ' && !argv[1][1]))
        return 0;
    
    // Validate that it contains only alphabetic characters
    int i = 0;
    while (argv[1][i])
    {
        if (!ft_isalpha(argv[1][i]))
            return 0;
        i++;
    }
    
    int len = ft_strlen(argv[1]);
    
    // Allocate a buffer for the result (current permutation)
    char *result = calloc(len + 1, 1);
    if (!result)
        return 1;
    
    // Sort the string alphabetically
    char *source = order_string(argv[1]);
    
    // Generate all permutations
    generate_permutations(source, result, 0);
    
    free(result);
    return 0;
}

/*
 * EXAMPLE EXECUTION:
 * 
 * ./permutations abc
 * abc
 * acb  
 * bac
 * bca
 * cab
 * cba
 * 
 * PROCESS FOR "abc":
 * 1. Sort: "abc" (already sorted)
 * 2. pos=0: Try 'a', 'b', 'c'
 *    - Choose 'a': result="a"
 *      - pos=1: Try 'b', 'c' (not 'a' because it is used)
 *        - Choose 'b': result="ab"
 *          - pos=2: Try 'c': result="abc" -> PRINT
 *        - Choose 'c': result="ac"
 *          - pos=2: Try 'b': result="acb" -> PRINT
 *    - Choose 'b': result="b"
 *      - Similar process...
 */

/*
 * ALTERNATIVE VERSION USING HEAP'S ALGORITHM:
 * (More efficient for long strings)
 */
// void heap_permute(char *str, int size)
// {
//     // Base case
//     if (size == 1)
//     {
//         puts(str);
//         return;
//     }
    
//     int i;
//     for (i = 0; i < size; i++)
//     {
//         heap_permute(str, size - 1);
        
//         // If size is odd, swap the first and last
//         // If size is even, swap the i-th and last
//         if (size % 2 == 1)
//             ft_swap(&str[0], &str[size - 1]);
//         else
//             ft_swap(&str[i], &str[size - 1]);
//     }
// }

/*
 * KEY POINTS FOR THE EXAM:
 * 
 * 1. ALPHABETICAL ORDER:
 *    - It is CRUCIAL to sort the string before generating permutations
 *    - Without sorting, alphabetical order is not guaranteed
 *    - Use a simple but correct sorting algorithm
 * 
 * 2. EFFICIENT BACKTRACKING:
 *    - Use an array of used characters for O(n) checking
 *    - Mark and unmark characters correctly
 *    - Do not forget to clear the state when returning
 * 
 * 3. MEMORY MANAGEMENT:
 *    - Allocate a buffer for the current permutation
 *    - Use calloc() to initialize it to '\0'
 *    - Free memory when finished
 * 
 * 4. ROBUST VALIDATION:
 *    - Check the number of arguments
 *    - Validate that it contains only letters
 *    - Handle special cases (empty string, spaces)
 * 
 * 5. OPTIMIZATIONS:
 *    - For strings with duplicate characters, use a different algorithm
 *    - For very long strings, consider Heap's algorithm
 *    - Avoid regenerating duplicate permutations
 */