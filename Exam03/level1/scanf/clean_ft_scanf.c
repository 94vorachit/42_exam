/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ft_scanf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 20:57:48 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 20:57:50 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:57:38 by vorhansa          #+#    #+#             */
/*   Updated: 2026/09/24 20:56:56 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// 5.
int match_space(FILE *f)
{
	int	ch = fgetc(f);
	if (ch == EOF && ferror(f))
		return (-1);
	while (ch != EOF)
	{
		if (!isspace(ch))
		{
			ungetc(ch, f);
			break;
		}
		ch = fgetc(f);
	}
	if (ferror(f))
		return (-1);
	return (1);
}

// 6.
int match_char(FILE *f, char c)
{
	int	ch = fgetc(f);
	if (ch == c)
		return (1);
	if (ch != EOF)
		ungetc(ch, f);
	return (-1);
}

// 2.
int scan_char(FILE *f, va_list ap)
{
	int	ch = fgetc(f);
	
	if (ch == EOF)
		return (-1);
		
	char	*cp = va_arg(ap, char *);
	*cp = (char)ch;
	return (1);
}

// 3.
int scan_int(FILE *f, va_list ap)
{
	int	ch = fgetc(f);
	
	if (ch == EOF)
		return (-1);

	while (isspace(ch))
		ch = fgetc(f);

	int	sign = 1;
	if (ch == '-')
	{
		sign = -1;
		ch = fgetc(f);
	}
	else if (ch == '+')
		ch = fgetc(f);
	
	if (!isdigit(ch))
	{
		ungetc(ch, f);
		return (-1);
	}

	int	value = 0;
	int	cnt = 0;
	while (isdigit(ch))
	{
		value = value * 10 + ch - '0';
		cnt++;
		ch = fgetc(f);
	}
	if (ch != EOF)
		ungetc(ch, f);

	if (cnt == 0)
		return (-1);
		
	int	*ip = va_arg(ap, int *);
	*ip = value * sign;
	return (1);
}

// 4.
int scan_string(FILE *f, va_list ap)
{
	int	ch = fgetc(f);
	
	while (ch != EOF && isspace(ch))
		ch = fgetc(f);
	
	if (ch == EOF)
		return (-1);

	char	*sp = va_arg(ap, char *);
	int		i = 0;
	do
	{
		sp[i] = ch;
		i++;
		ch = fgetc(f);
	} while (ch != EOF && !isspace(ch));
	
	sp[i] = '\0';
	
	if (ch != EOF)
		ungetc(ch, f);
	
	if (i == 0)
		return (-1);
	return (1);
}

// DNT
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

// DNT
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}

// 1.
int ft_scanf(const char *format, ...)
{
	va_list	ap;
	
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	
	return ret;
}

// int main(void)
// {
//     int x;
//     char str[100];
//     char c;

//     // Leer: número, espacio, string, espacio, carácter
//     int converted = ft_scanf("%d %s %c", &x, str, &c);
    
//     printf("Convertidos: %d\n", converted);
//     printf("Número: %d, String: %s, Carácter: %c\n", x, str, c);
    
//     return 0;
// }