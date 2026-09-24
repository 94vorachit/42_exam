/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:22:39 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 18:35:00 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 42
#include <string.h> // memmove, strlen
#include <stdio.h> // perror
#include <unistd.h> // ssize_t, read
#include <stdlib.h> // realloc, free

void	ft_filter(char *buf, const char *tar)
{
	int	i = 0;
	int	tar_len = strlen(tar);

	while (buf[i])
	{
		int	j = 0;
		while (tar[j] && (buf[i + j] == tar[j]))
			j++;
		if (j == tar_len)
		{
			int	k = 0;
			while (k++ < tar_len)
			// {
				write(1, "*", 1);
				// k++;
			// }
			i += tar_len;
		}
		else
			write(1, &buf[i++], 1);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	
	char	temp[BUFFER_SIZE];
	char	*result = NULL;
	char	*buffer;
	size_t	total_read = 0;
	ssize_t	bytes;

	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(result);
			perror("realloc");
			return (1);
		}

		result = buffer;

		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0';
	}

	if (bytes < 0)
	{
		perror("read");
		free(result);
		return (1);
	}

	if (!result)
		return (0);

	// printf("%s", result);
	ft_filter(result, av[1]);
	free(result);
	return (0);
}

/*
#define BUFFER_SIZE 42
#include <string.h> // memmove, strlen
#include <stdio.h> // perror
#include <unistd.h> // ssize_t, read , write
#include <stdlib.h> // realloc, free

void	ft_filter(char *buf, const char *tar)
{
	int	i = 0;
	int	tar_len = strlen(tar);

	while (buf[i])
	{
		int	j = 0;
		while (tar[j] && (buf[i + j] == tar[j]))
			j++;
		if (j == tar_len)
		{
			int	k = 0;
			while (k++ < tar_len)
			// {
				write(1, "*", 1);
				// k++;
			// }
			i += tar_len;
		}
		else
			write(1, &buf[i++], 1);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	
	char	temp[BUFFER_SIZE];
	char	*result = NULL;
	char	*buffer;
	size_t	total_read = 0;
	ssize_t	bytes;

	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(result);
			perror("realloc");
			return (1);
		}

		result = buffer;

		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0';
	}

	if (bytes < 0)
	{
		perror("read");
		free(result);
		return (1);
	}

	if (!result)
		return (0);

	// printf("%s", result);
	ft_filter(result, av[1]);
	free(result);
	return (0);
}
*/