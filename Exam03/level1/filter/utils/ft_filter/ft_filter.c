/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:24:51 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 17:36:08 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
// #include <stdlib.h>
#include <string.h>

void	ft_filter(char *buf,const char *tar)
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
				write(1, "*", 1);
			i += tar_len;
		}
		else
			write(1, &buf[i++], 1);
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		return (1);

	ft_filter(av[1], av[2]);
	return (0);
}
