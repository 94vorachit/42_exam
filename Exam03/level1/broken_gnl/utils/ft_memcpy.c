/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:34 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 15:23:30 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The memcpy() function in C is used to copy a specified number of bytes from one 
memory location to another. It is widely used for copying arrays, structures, 
and blocks of memory efficiently.

* Defined in the <string.h> header file.
* Copies data in a byte-by-byte manner.
* Works with raw memory addresses regardless of the data type.
* Commonly used for fast memory manipulation operations.
*/

#include <sys/types.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;

	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

int	main(void)
{
	char	str1[] = "Hello World";
	char	str2[] = "";

	printf("str2 before memcpy : %s\n", str2);
	ft_memcpy(str2, str1, sizeof(str1));
	printf("str2 after memcpy : %s\n", str2);
	return (0);
}
