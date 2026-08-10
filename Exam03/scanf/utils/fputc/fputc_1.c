/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fputc_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 19:19:44 by vorhansa          #+#    #+#             */
/*   Updated: 2026/06/29 19:26:14 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int	i = 0;
	FILE	*fp = fopen("output.txt", "w");

	if (fp == NULL)
		return (0);

	char	str[] = "good bye", received_str[20];
	
	while (str[i] != '\0')
	{
		fputc(str[i], fp);
		i++;
	}
	fclose(fp);
	fp = fopen("output.txt", "r");
	fgets(received_str, 20, fp);
	printf("%s", received_str);
	fclose(fp);
	return (0);
}
