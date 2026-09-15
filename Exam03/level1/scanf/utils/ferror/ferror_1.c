/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ferror_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:22:57 by vorhansa          #+#    #+#             */
/*   Updated: 2026/07/06 18:28:38 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE *fptr = fopen("test.txt", "w");

	fprintf(fptr, "Helle, TEST!");

	if (ferror(fptr) == 0)
		printf("Data written successfully.");
	fclose(fptr);
	return (0);
}
