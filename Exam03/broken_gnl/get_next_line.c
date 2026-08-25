/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 17:36:28 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 19:16:01 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	/*if (dest > src)
	return ft_memmove(dest, src, n);
	else if (dest == src)
	return dest;
	size_t i = ft_strlen((char *)src) - 1;
	while (i >= 0)
	{
	((char *)dest)[i] = ((char *)src)[i];
	i--;
	}
	return dest;*/

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

char *get_next_line(int fd)
{
	/*static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while(!tmp)
	{
	if (!str_append_str(&ret, b))
		return (NULL);
	int read_ret = read(fd, b, BUFFER_SIZE);
	if (read_ret == -1)
		return (NULL);
	b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
	free(ret);
	return NULL;
	}
	return ret;*/

	static char	b[BUFFER_SIZE + 1] = "";
	char				*ret = NULL;
	char				*temp;
	int					read_ret;

	while (1)
	{
		temp = ft_strchr(b, '\n');
		if (temp)
		{
			if (!str_append_mem(&ret, b, temp - b + 1))
				return (free(ret), NULL);
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1);
			return (ret);
		}
		
		if (!str_append_str(&ret, b))
			return (NULL);

		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			b[0] = '\0';
			if (ret && *ret)
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = '\0';
	}
}
