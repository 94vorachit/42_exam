/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feof_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:44:43 by vorhansa          #+#    #+#             */
/*   Updated: 2026/07/06 18:54:38 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*fptr = fopen("file.txt", "w");
	char	ch;

	ch = fgetc(fptr);
	
	if (ch == EOF)
		printf("End of file or unable to read");
	else
		printf("Read character: %c", ch);
	fclose(fptr);
	return (0);
}

/*
In the above program, the getc() function should be unable to read as the file
is opened in the write mode only. But it still returns EOF because of which it 
becomes difficult to find the source of error. Here, the feof() function can 
be specifically used to check for End of File.
*/