/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_permutations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:55:15 by vorhansa          #+#    #+#             */
/*   Updated: 2026/10/09 19:26:33 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void	ft_swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_strchr(char *s, char c)
{
	int	i  = 0;
	
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *ft_order_string(char *s)
{
	int	swap_flag = 1;
	while (swap_flag)
	{
		swap_flag = 0;
		int	i = 0;
		while (s[i] && s[i + 1])
		{
			if (s[i] > s[i + 1])
			{
				ft_swap(&s[i], &s[i + 1]);
				swap_flag = 1;
			}
			i++;
		}
	}
	return (s);
}

void	ft_generate(char *res, char *src, int pos)
{
	int	len = ft_strlen(src);
	if (pos == len)
	{
		write(1, res, len);
		write(1, "\n", 1);
		return ;
	}
	
	int	i = 0;
	while (i < len)
	{
		if (!ft_strchr(res, src[i]))
		{
			res[pos] = src[i];
			ft_generate(res, src, pos + 1);
			res[pos] = '\0';
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (ft_strlen(av[1]) == 0 || (av[1][0] == ' ' && !av[1][1]))
		return (0);
	
	int	i = 0;
	while (av[1][i])
	{
		if (!ft_isalpha(av[1][i]))
			return (0);
		i++;
	}

	int	len = ft_strlen(av[1]);
	char *res = calloc(len + 1, 1);
	if (!res)
	{
		free(res);
		return (1);
	}

	char *src = ft_order_string(av[1]);
	ft_generate(res, src, 0);
	free(res);
	return (0);
}
