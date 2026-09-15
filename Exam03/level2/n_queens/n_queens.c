/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 23:22:27 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/03 23:13:17 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_abs(int x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	char c = (n % 10) + '0';
	write(1, &c, 1);
}

void	ft_print_pos(int *pos, int n)
{
	int	i = 0;
	
	while (i < n)
	{
		ft_putnbr(pos[i]);
		if (i < n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	ft_is_safe(int *pos, int col, int row)
{
	int	i = 0;
	
	while (i < col)
	{
		if (pos[i] == row)
			return (0);
		if (ft_abs(pos[i] - row) == col - i)
			return (0);
		i++;
	}
	return (1);
}

void	ft_solve(int *pos, int n, int col)
{
	int	row = 0;

	while (row < n)
	{
		if (ft_is_safe(pos, col, row))
		{
			pos[col] = row;
			ft_solve(pos, n, col + 1);
		}
		row++;
	}
	if (col == n)
		return (ft_print_pos(pos, n));
}

int	main(int ac, char **av)
{
	int	n;
	int	*pos;
	
	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	if (n <= 0)
		return (0);
	pos = malloc(sizeof(int) * n);
	if (!pos)
		return (1);
	ft_solve(pos, n, 0);
	free(pos);
	return (0);
}
