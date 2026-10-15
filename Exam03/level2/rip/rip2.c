/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 02:48:10 by vorhansa          #+#    #+#             */
/*   Updated: 2026/10/16 03:01:19 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_is_balance(char *s, int len)
{
	int	bal = 0;
	int	i = 0;
	
	while (i < len)
	{
		if (s[i] == '(')
			bal++;
		else if (s[i] == ')')
		{
			bal--;
			if (bal < 0)
				return (0);
		}
		i++;
	}
	return (bal == 0);
}

void	ft_solve(char *s, int *min, int index, int current, int print)
{
	if (current > *min)
		return ;
	if (ft_is_balance(s, ft_strlen(s)))
	{
		if (!print && current < *min)
			*min = current;
		else if (print && current == *min)
		{
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
		}
		return ;
	}
	
	int	i = index;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')')
		{
			char saved = s[i];
			s[i] = ' ';
			ft_solve(s, min, i + 1, current + 1, print);
			s[i] = saved;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
		
	int	i = 0;
	while (av[1][i])
	{
		if (av[1][i] == '(' && av[1][i] == ')')
			return (1);
		i++;
	}
	
	int	min = ft_strlen(av[1]);
	ft_solve(av[1], &min, 0, 0, 0);
	ft_solve(av[1], &min, 0, 0, 1);
	return (0);
}