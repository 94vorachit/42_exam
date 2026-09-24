/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ferror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 20:31:50 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 20:32:41 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Attempting an invalid operation: writing to a read-only file stream
    fputc('A', file); 

    // Check if the write operation triggered a stream error
    if (ferror(file)) {
        printf("A stream error was detected!\n");
        
        // Print the system-level error reason
        perror("Reason for error"); 
        
        // Reset the stream indicators if you intend to keep using the file
        clearerr(file); 
    }

    fclose(file);
    return 0;
}
