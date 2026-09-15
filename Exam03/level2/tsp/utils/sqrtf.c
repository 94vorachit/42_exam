/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrtf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:15:25 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/15 18:17:11 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

typedef struct
{
	float	x;
	float	y;
} city;

float	cal_dis(city a, city b)
{
	float	dx = a.x - b.x;
	float	dy = a.y - b.y;
	return (sqrtf(dx * dx + dy * dy));
}

int	main(int ac, char **av)
{
	// city	a;
	// city	b;
	
	// a.x = 0.0f; a.y = 0.0f;
	// b.x = 3.0f; b.y = 4.0f;
	city	cities[12];
	int		n = 0;

	while (fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
	{
		printf("n = %d, %f, %f\n", n, cities[n].x, cities[n].y);
		n++;
	}
	printf("sqrtf : %.7f\n", cal_dis(cities[0], cities[1]));
	return (0);
}
