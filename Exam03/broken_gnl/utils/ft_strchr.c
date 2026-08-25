/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 14:57:34 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 15:08:54 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*
The strchr() function in C is a predefined string handling function declared in 
the <string.h> header file. It is used to find the first occurrence of a 
specified character in a string.
* Returns a pointer to the first occurrence of the character if it is found.
* Character is not present in the string, it returns NULL.
*/

char	*ft_strchr(char *s, int c)
{
	int	i = 0;

	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	char	str[] = "Hello World";
	char	*ptr = ft_strchr(str, 'W');

	if (ptr != NULL)
		printf("Character found at position: %ld\nptr : %s\n", ptr - str, ptr);
	else
		printf("Character not found\n");
	return (0);
}
