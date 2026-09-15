/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgetc_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 01:29:23 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/24 01:46:41 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*file = fopen("example2.txt", "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	int	ch;
	int	count = 0;
	while ((ch = fgetc(file)) != EOF)
		count++;
	printf("Total number of characters: %d\n", count);
	fclose(file);
	return (0);
}
