/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 18:21:56 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 18:26:10 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;
	
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
	/*while(--n > 0)
	((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return dest;*/
}

size_t ft_strlen(char *s)
{
	/*
	size_t res = 0;
	while (*s)
	{
	s++;
	res++;
	}
	return res;*/
	size_t	len = 0;
	
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	/*size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
	return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1; */
	size_t	size1;
	char		*tmp;

	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;

	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);

	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

static int	check_string(const char *label, const char *actual, const char *expected)
{
	if (!actual || strcmp(actual, expected) != 0)
	{
		fprintf(stderr, "FAIL: %s\nexpected: [%s]\nactual:   [%s]\n",
			label, expected, actual ? actual : "(null)");
		return (0);
	}
	printf("PASS: %s -> [%s]\n", label, actual);
	return (1);
}

int	main(void)
{
	char	*buffer;
	int		ok;

	buffer = NULL;
	ok = str_append_mem(&buffer, "abc", 3);
	if (!ok || !check_string("append into NULL", buffer, "abc"))
		return (free(buffer), 1);
	ok = str_append_mem(&buffer, "de", 2);
	if (!ok || !check_string("append to existing string", buffer, "abcde"))
		return (free(buffer), 1);
	ok = str_append_mem(&buffer, "ignored", 0);
	if (!ok || !check_string("append zero bytes", buffer, "abcde"))
		return (free(buffer), 1);
	free(buffer);
	puts("All str_append_mem tests passed.");
	return (0);
}
