/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:17:41 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/10 17:53:23 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* EXERCISE: FILTER
*
* DESCRIPTION:
* Read from stdin and write to stdout, but replacing all occurrences
* of a given string with asterisks (*) of the same length.
*
* KEY CONCEPTS:
* 1. DYNAMIC READING: read() with a variable buffer
* 2. PATTERN SEARCHING: strstr() or memmem()
* 3. MEMORY MANAGEMENT: realloc() for dynamic buffer
* 4. ERROR HANDLING: perror() for system errors
*
* ALGORITHM:
* 1. Read the entire content from stdin into a dynamic buffer
* 2. Find all occurrences of the pattern
* 3. Replace each occurrence with asterisks
* 4. Write the result to stdout
*/

#define _GNU_SOURCE // Para memmem()
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Function to find and replace all occurrences
void	ft_filter(char *buffer, const char *target)
{
	int	i = 0;
	int	target_len = strlen(target);
	int	j, k;

	/*
	* SEARCH AND REPLACE ALGORITHM:
	* - Go through the buffer character by character
	* - At each position, check if it matches the pattern
	* - If it matches, write asterisks and skip the length of the pattern
	* - If it doesn't match, write the original character
	*/

	while (buffer[i])
	{
		j = 0;
		// Check if there is a match from the current position
		while (target[j] && (buffer[i + j] == target[j]))
			j++;
		
		if (j == target_len) // Full match found
		{
			// Write asterisks instead of the pattern
			k = 0;
			while (k < target_len)
			{
				write(1, "*", 1);
				k++;
			}
			i += target_len; // Skip the entire pattern
		}
		else
		{
			// No match, write original character
			write(1, &buffer[i], 1);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	/*
	* ARGUMENT VALIDATION:
	* - There must be exactly 1 argument
	* - The argument cannot be empty
	*/
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	
	/*
	* DYNAMIC READING FROM STDIN:
	* - Use a temporary buffer to read chunks
	* - Use realloc() to expand the main buffer
	* - Keep track of the total read
	*/
	char	temp[BUFFER_SIZE];
	char	*result = NULL;
	char	*buffer;
	int		total_read = 0;
	ssize_t	bytes;

	// Read from stdin until EOF
	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		// Expand the main buffer to accommodate the new data
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(result);
			perror("realloc");
			return (1);
		}

		result = buffer;

		// Copy the new data to the main buffer
		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0'; // Ensure completion
	}

	// Check for reading errors
	if (bytes < 0)
	{
		perror("read");
		free(result);
		return (1);
	}
	
	// If nothing was read, exit without error
	if (!result)
		return (0);

	// Process the buffer and apply the filter
	ft_filter(result, av[1]);

	// Free memory
	free(result);
	return (0);
}

/*
* KEY POINTS FOR THE EXAM:
*
* 1. MEMORY MANAGEMENT:
* - Always check the return of malloc/realloc
* - Free memory in case of error
* - Use memmove() instead of memcpy() for overlaps
*
* 2. ERROR HANDLING:
* - Use perror() for system errors
* - Return appropriate error codes
* - Validate arguments before using them
*
* 3. DYNAMIC READING:
* - The buffer can be filled with any amount of data
* - Use realloc() to expand as needed
* - Keep a valid null terminator
*
* 4. EFFICIENT ALGORITHM:
* - Simple character-by-character search
* - Avoid using non-allowed functions
* - Write directly to stdout without storing the result
*/
