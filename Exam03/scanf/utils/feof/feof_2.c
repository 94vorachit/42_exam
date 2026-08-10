/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feof_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:50:18 by vorhansa          #+#    #+#             */
/*   Updated: 2026/07/06 18:56:11 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*fptr = fopen("file2.txt", "w");
	char	ch;

	ch = getc(fptr);
	if (ch == EOF)
	{
		if (feof(fptr) == EOF)
			printf("End of file");
		else
			printf("Unable to read");
	}
	else
		printf("Read Character: %c", ch);
	fclose(fptr);
	return (0);
}
