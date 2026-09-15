/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 17:17:38 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/25 19:13:51 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL
# define GNL

#include <stdio.h> //
/*
optional, mostly for standard I/O/debugging
Gives access to memory functions like malloc, free, and realloc.
In a GNL implementation, this is used to allocate buffers dynamically.
*/

#include <stdlib.h>
/*
allocate memory
Gives access to standard I/O functions such as printf, fopen, fread, etc.
In GNL, this is usually not mandatory unless you use debug prints or file operations from stdio.
It is common, but not always essential for this project.
*/

#include <unistd.h>
/*
read data from fd
This is very important for GNL.
It provides read, write, and close, which are exactly the functions used to read from a file descriptor.
Without this, you cannot read the input stream properly.
*/

#include <sys/types.h>
/*
needed types
Defines types like ssize_t, size_t, off_t, etc.
These are often required by functions like read() and open().
It is a support header for low-level system functions.
*/

#include <fcntl.h>
/*
open file descriptors
Gives access to open() and flags like O_RDONLY.
This is used to open files for reading, which is common in GNL.
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif