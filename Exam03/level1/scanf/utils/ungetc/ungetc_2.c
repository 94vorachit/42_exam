/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ungetc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 18:44:50 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/29 18:49:38 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// C program for taking input till we
// get 1 at the input 
int	main(void)
{
	int	ch;
	
	// reads characters from the stdin and show
    // them on stdout until encounters '1'
	while ((ch = getchar()) != '1')
		putchar(ch);
		
	// ungetc() returns '1' previously
    // read back to stdin
	ungetc(ch, stdin);

	// getchar() attempts to read
    // next character from stdin
    // and reads character '1' returned
    // back to the stdin by ungetc()
	ch = getchar();

	// putchar() displays character
	putchar(ch);
	return (0);
}
