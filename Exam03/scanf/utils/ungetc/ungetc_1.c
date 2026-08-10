/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ungetc_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 18:25:39 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/29 18:51:36 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	FILE	*f;
	int		ch;
	char	buffer[256];
	
	// read a file
	f = fopen("Example1.txt", "r");

	// when no data
	if (f == NULL)
	{
		printf("Error in openong file");
		return (-1);
	}
	
	// read lines till end
	while (!feof(f))
	{
		// get line
		ch = getc(f);
		// replace ! with +
		if (ch == '!')
			ungetc('+', f);
		// if not
		else
			ungetc(ch, f);
		fgets(buffer, 255, f);
		fputs(buffer, stdout);
	}
	return (0);
}
