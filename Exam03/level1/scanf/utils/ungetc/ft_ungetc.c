/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ungetc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 20:18:00 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 20:18:11 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int main(void) 
{
    int ch;

    printf("Enter some digits followed by letters (e.g., 123xyz): ");

    // 1. Read all consecutive digits
    while ((ch = getchar()) != EOF && isdigit(ch)) {
        putchar(ch); 
    }

    // 2. We hit a non-digit character. Put it back into the stream!
    if (ch != EOF) {
        ungetc(ch, stdin);
    }

    // 3. The next read operation will pick up exactly where we left off
    printf("\nThe next character remaining in the stream is: '%c'\n", getchar());

    return 0;
}
