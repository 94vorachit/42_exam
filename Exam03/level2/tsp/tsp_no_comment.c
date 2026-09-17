/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp_no_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:25:37 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/17 17:54:12 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <float.h>

typedef	struct
{
	float	x, y;
} s_city;

float	ft_cal_dis(s_city a, s_city b)
{
	float	dx = a.x - b.x;
	float	dy = a.y - b.y;
	return (sqrtf(dx * dx + dy * dy));
}

float	ft_cal_total_dis(s_city *cities, int *path, int n)
{
	float total = 0.0f;
	int	i;

	for (i = 0; i < n - 1; i++)
	{
		total += ft_cal_dis(cities[path[i]], cities[path[i + 1]]);
		printf("first : %.2f, %.2f\n", cities[path[i]].x, cities[path[i]].y);
		printf("second : %.2f, %.2f\n", cities[path[i + 1]].x, cities[path[i + 1]].y);
		printf("ft_cal_total_dis| i : %d, n : %d, total : %f\n", i, n, total);
	}	
	total += ft_cal_dis(cities[path[n - 1]], cities[path[0]]);
	printf("first : %.2f, %.2f\n", cities[path[n - 1]].x, cities[path[n - 1]].y);
	printf("second : %.2f, %.2f\n", cities[path[path[0]]].x, cities[path[0]].y);
	printf("ft_cal_total_dis| i : %d, n : %d, total : %f\n", i, n, total);
	return (total);
}

void	ft_swap(int *a, int *b)
{
	int	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_find_short_path(s_city *cities, int *path, int n, int pos, float *min_dis)
{
	if (pos == n)
	{
		float total = ft_cal_total_dis(cities, path, n);
		if (total < *min_dis)
			*min_dis = total;
		return;
	}

	for (int i = pos; i < n; i++)
	{
		/* debug: print pos, i and current minimum distance */
		/* use %f and dereference min_dis (float pointer) to avoid UB */
		ft_swap(&path[pos], &path[i]);
		ft_find_short_path(cities, path, n, pos + 1, min_dis);
		ft_swap(&path[pos], &path[i]);
		printf("ft_find_short_path| pos : %d, i : %d, min_dis : %f\n", pos, i, *min_dis);
	}
}

int	main(void)
{
	s_city	cities[12];
	int	n = 0;
	
	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;

	if (n < 2)
	{
		printf("0.00\n");
		return (0);
	}

	int	path[12];
	for (int i = 0; i < n; i++)
		path[i] = i;

	float	min_dis = FLT_MAX;
	ft_find_short_path(cities, path, n, 1, &min_dis);
	printf("%.2f\n", min_dis);
	return (0);
}
