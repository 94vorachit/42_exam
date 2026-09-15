/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 14:11:00 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/08 19:30:19 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

// function to check if a string is balanced
int	ft_is_balanced(char *str, int len)
{
	/*
	* PARENTHESES VALIDATION ALGORITHM:
	* Use a counter for open parentheses
	* Increment by '(', decrement by ')'
	* If the counter is less than 0 at any time: unbalanced
	* The counter must be 0 at the end
	*/
	int	balance = 0;
	int	i = 0;

	while (i < len)
	{
		if (str[i] == '(')
			balance++;
		else if(str[i] == ')') // More ')' than '(' so far
		{
			balance--;
			if (balance < 0)
				return (0);
		}
		// Ignore spaces (removed characters)
		i++;
	}
	return (balance == 0); // Balanced if final counter is 0
}

// Function to find the minimum number of removals needed
void ft_find_min_removals(char *str, int *min_removals, int index, int current_removals)
{
    if (current_removals > *min_removals)
        return;
    if (ft_is_balanced(str, ft_strlen(str)))
    {
        if (current_removals < *min_removals)
            *min_removals = current_removals;
        return;
    }
    
    int i = index;
    while (str[i])
    {
        if (str[i] == '(' || str[i] == ')')
        {
            char saved = str[i];
            str[i] = ' ';
            
            ft_find_min_removals(str, min_removals, i + 1, current_removals + 1);
            
            str[i] = saved;
        }
        i++;
    }
}

void ft_generate_solutions(char *str, int min_removals, int index, int current_removals)
{
    if (current_removals > min_removals)
        return;
    if (ft_is_balanced(str, ft_strlen(str)) && current_removals == min_removals)
    {
        write(1, str, ft_strlen(str));
        write(1, "\n", 1);
        return;
    }
	
	int	i = index;
    while (str[i])
    {
        if (str[i] == '(' || str[i] == ')')
        {
            char saved = str[i];
            str[i] = ' ';  
            ft_generate_solutions(str, min_removals, i + 1, current_removals + 1);
            str[i] = saved;
		}
        i++;
    }
}


int	main(int ac, char **av)
{
	/*
	* VALIDATION AND PROCESSING:
	* - Verify valid arguments
	* - Validate that it only contains parentheses
	* - Find the minimum number of removals
	* - Generate all solutions with that minimum
	*/
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	
	// Validate that the string only contains parentheses
	int	i = 0;
	while (av[1][i])
	{
		if (av[1][i] != '(' && av[1][i] != ')')
			return (1);
		i++;
	}
	
	// Initialize with the maximum possible
	int	min_removals = ft_strlen(av[1]);
	
	ft_find_min_removals(av[1], &min_removals, 0, 0);
    ft_generate_solutions(av[1], min_removals, 0, 0);
    return 0;
}

/*
* EXAMPLE EXECUTION:
* 
* ./rip '(()'
* 
* PROCESS:
* 1. Original string: "(()"
* 2. Check if it is balanced: NO (final balance = 1)
* 3. Find the minimum:
*    - Remove first '(': "())" → balance = -1 → INVALID
*    - Remove second '(': "())" → balance = -1 → INVALID
*    - Remove ')': "((" → balance = 2 → INVALID
*    - Remove first '(' and ')': " ()" → balance = 0 → VALID (1 removal)
*    - Remove second '(' and ')': "( )" → balance = 0 → VALID (1 removal)
* 4. Minimum = 1
* 5. Generate solutions with 1 removal:
*    - " ()" → Print
*    - "( )" → Print
* 
* Output:
*  ()
* ( )
*/

/*
* OPTIMIZED ALGORITHM (for complex cases):
* 
* void rip_optimized(char *str)
* {
*     // Count unbalanced parentheses
*     int open = 0, close = 0;
*     
*     // First pass: count excess ')' 
*     for (int i = 0; str[i]; i++)
*     {
*         if (str[i] == '(')
*             open++;
*         else if (str[i] == ')' && open > 0)
*             open--;
*         else if (str[i] == ')')
*             close++;  // ')' without a matching '('
*     }
*     
*     // open = excess '(', close = excess ')'
*     // Total to remove = open + close
*     
*     generate_solutions_optimized(str, 0, 0, open, close);
* }
*/

/*
* SPECIAL CASES:
* 
* 1. Already balanced string: "()" → Remove nothing
* 2. Only opening parentheses: "(((" → Remove all
* 3. Only closing parentheses: ")))" → Remove all
* 4. Empty string: "" → Already balanced
* 5. Single parenthesis: "(" or ")" → Remove the only one
*/

/*
* KEY POINTS FOR THE EXAM:
* 
* 1. PARENTHESES VALIDATION:
*    - Classic counter-based algorithm
*    - balance++ for '(', balance-- for ')'
*    - balance < 0 at any moment = invalid
*    - balance == 0 at the end = valid
* 
* 2. BACKTRACKING IN TWO PHASES:
*    - Phase 1: Find the minimum number of removals
*    - Phase 2: Generate all solutions with that minimum
*    - Use the same recursive structure for both
* 
* 3. REMOVAL REPRESENTATION:
*    - Replace with space ' ' instead of deleting
*    - Easier than handling variable-length strings
*    - Restore the original character after each attempt
* 
* 4. EFFICIENT PRUNING:
*    - Stop if current_removals > min_removals
*    - Avoid exploring unnecessary branches
*    - Crucial for performance on long strings
* 
* 5. MULTIPLE SOLUTIONS:
*    - There may be several ways to remove the minimum
*    - Generate all of them systematically
*    - Do not allow duplicates (the exploration order matters)
*/