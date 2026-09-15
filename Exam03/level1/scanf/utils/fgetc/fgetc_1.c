/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fgetc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:53:16 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/24 00:52:53 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*
	int fgetc(FILE *stream);

	Parameter : stream 
	A pointer to a FILE object that identifies the input stream.
	This stream is usually obtained by opening a file using the fopen function.

	Return Value : 
	The function returns the character read from the stream as an unsigned 
	char cast to an int.If the end-of-file is encountered or an error occurs, 
	the function returns EOF, which is a macro typically defined as -1. 
	To distinguish between an actual character and an EOF return, 
	one should use the feof or ferror functions to check if the end of 
	the file or an error has occurred.
*/

int	main()
{
	FILE	*file = fopen("example1.txt", "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	
	int	ch = fgetc(file);
	if (ch != EOF)
		printf("The first character is: %c\n", ch);
	else
		printf("No characters to read or error reading file\n");
	fclose(file);
	return (0);
}
