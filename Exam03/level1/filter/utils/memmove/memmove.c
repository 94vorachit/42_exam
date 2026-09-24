/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:51:05 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 16:52:47 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "abcdef";

    // Goal: Shift "abc" two positions to the right to make it "abcdef" -> "ababcf"
    // Source: "abc" (starts at str)
    // Destination: starts at str + 2
    // Number of bytes: 3 ('a', 'b', 'c')
    
    printf("Before: %s\n", str);

    // Using memmove safely handles the overlap
    memmove(str + 2, str, 3);

    printf("After:  %s\n", str); // Outputs: ababcf
    return 0;
}