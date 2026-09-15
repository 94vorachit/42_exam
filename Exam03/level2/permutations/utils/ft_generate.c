/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 14:38:31 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/15 14:47:12 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strchr(char *s, char c)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_generate(char *src, char *res, int pos)
{
	int	src_len = ft_strlen(src);

	if (pos == src_len)
	{
		write(1, res, src_len);
		write(1, "\n", 1);
		return;
	}

	int	i = 0;
	while (i < src_len)
	{
		if (!ft_strchr(res, src[i]))
		{
			res[pos] = src[i];
			ft_generate(src, res, pos + 1);
			res[pos] = '\0';
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	len = ft_strlen(av[1]);
	char *res = calloc(len + 1, 1);
	if (!res)
		return (1);
	char *src = av[1];
	ft_generate(src, res, 0);
	free(res);
	return (0);
}
