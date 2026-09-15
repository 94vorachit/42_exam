/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 18:43:59 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 18:51:57 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}

static int check_case(const char *name, const unsigned char *buffer,
					const unsigned char *expected, size_t size)
{
	if (memcmp(buffer, expected, size) != 0)
	{
		printf("%s: fail\n", name);
		return (1);
	}
	printf("%s: pass\n", name);
	return (0);
}

int main(void)
{
	int			fails;
	unsigned char	plain_copy[5] = {'h', 'e', 'l', 'l', 'o'};
	const unsigned char	plain_expected[5] = {'w', 'o', 'r', 'l', 'd'};
	unsigned char	forward_overlap[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};
	const unsigned char	forward_expected[10] = {'c', 'd', 'e', 'f', 'g', 'h', 'g', 'h', 'i', '\0'};
	unsigned char	backward_overlap[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};
	const unsigned char	backward_expected[10] = {'a', 'b', 'a', 'b', 'c', 'd', 'e', 'f', 'i', '\0'};

	fails = 0;
	ft_memmove(plain_copy, "world", 5);
	fails += check_case("plain-copy", plain_copy, plain_expected, sizeof(plain_copy));
	ft_memmove(forward_overlap, forward_overlap + 2, 6);
	fails += check_case("forward-overlap", forward_overlap, forward_expected, sizeof(forward_overlap));
	ft_memmove(backward_overlap + 2, backward_overlap, 6);
	fails += check_case("backward-overlap", backward_overlap, backward_expected, sizeof(backward_overlap));
	return (fails != 0);
}
