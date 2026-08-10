/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ferror_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:29:43 by vorhansa          #+#    #+#             */
/*   Updated: 2026/07/06 18:36:55 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*fptr = fopen("test2.txt", "w+");
	fprintf(fptr, "TEST!");
	
	rewind(fptr);
	char	d[5];
	while (fscanf(fptr, "%s", d) != EOF)

	if (ferror(fptr) == 0)
	{
		for (int i = 0; i < sizeof(d); i++)
			printf("%c", d[i]);
		printf("\nNo error, Data read successfully");
	}
	fclose(fptr);
	return (0);
}
