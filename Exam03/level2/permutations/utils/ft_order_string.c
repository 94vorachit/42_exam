/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_order_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 17:02:58 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/14 17:16:10 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void	ft_swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

char	*ft_order_string(char *s)
{
	int	len = ft_strlen(s);
	int	swapped = 1;

	while (swapped)
	{
		swapped = 0;
		int	i = 0;
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
	return (s);
}

int main(int ac, char **av)
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
    
    char *src = ft_order_string(av[1]);
    
    printf("%s\n", src);
}
