/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fscanf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 17:40:08 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/15 18:00:46 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct
{
	float x, y;
} city;

int	main(void)
{
	city	cities[12];
	int		n = 0;

	while (fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
	{
		printf("%f, %f\n", cities[n].x, cities[n].y);
		n++;
	}
	return (0);
}