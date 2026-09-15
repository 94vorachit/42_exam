/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgetc_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:10:31 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/29 19:13:28 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*fp = fopen("test.txt", "r");

	if (fp == NULL)
		return (0);
	do
	{
		char	c = fgetc(fp);
		if (feof(fp))
			break;
		printf("%c", c);
	} while (1);
	fclose(fp);
	return (0);
}
