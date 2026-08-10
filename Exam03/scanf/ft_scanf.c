/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorhansa <vorhansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:02:01 by vorhansa          #+#    #+#             */
/*   Updated: 2026/08/10 18:21:49 by vorhansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* EXERCISE: FT_SCANF
*
* DESCRIPTION:
* Implement a simplified version of scanf that only handles %s, %d, and %c.
*
* KEY CONCEPTS:
* 1. VARIABLE ARGUMENTS: va_list, va_start, va_arg, va_end
* 2. FORMAT PARSING: Parse the format string character by character
* 3. FILE READING: fgetc(), ungetc() for flow control
* 4. CONVERSIONS: Convert strings to numbers, handle whitespace
*
* SUPPORTED FORMAT:
* - %s: string (up to the first whitespace)
* - %d: decimal integer (optional sign)
* - %c: single character
*/

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

// Function to skip whitespace in the stream
int	match_space(FILE *f)
{
    /*
    * HANDLING WHITESPACE:
    * - Read characters while they are whitespace
    * - Push the first non-space character back into the stream
    * - Return -1 on error
    */
	int	ch = fgetc(f);
	if (ch == EOF && ferror(f))
		return (-1);
	while (ch != EOF)
	{
		if (!isspace(ch))
		{
			ungetc(ch, f); // Return non-space character
			break;
		}
		ch = fgetc(f);
	}
	if (ferror(f))
		return (-1);
	return (1);
}

// Function to match a specific character
int	match_char(FILE *f, char c)
{
    /*
    * LITERAL CHARACTER MATCHING:
    * - Read a character from the stream
    * - Check if it matches the expected one
    * - Push it back to the stream if it doesn't match
    */
	int	ch = fgetc(f);
	if (ch == c)
		return (1);
	if (ch != EOF)
		ungetc(ch, f);
	return (-1);
}

// Function to read a character (%c)
int	scan_char(FILE *f, va_list ap)
{
    /*
    * CONVERSION %c:
    * - Read exactly one character
    * - Do not skip whitespace
    * - Store it into the provided pointer
    */
	int	ch = fgetc(f);
	char *cp = va_arg(ap, char *);
	if (ch == EOF)
		return (-1);
	*cp = (char)ch;
	return (1);
}

// Function to read an integer (%d)
int	scan_int(FILE *f, va_list ap)
{
    /*
    * CONVERSION %d:
    * - Skip initial whitespace
    * - Read optional sign (+/-)
    * - Read digits and build the number
    * - Push the last non-digit character back to the stream
    */
	int	ch = fgetc(f);
	int	sign = 1;
	int	value = 0;
	int	count = 0;
	int	*ip = va_arg(ap, int *);
	
	if (ch == EOF)
		return (-1);
	
	// Skip spaces
	while (isspace(ch))
		ch = fgetc(f);
	
	// Handle sign
	if (ch == '-')
	{
		sign = -1;
		ch = fgetc(f);
	}
	else if (ch == '+')
		ch = fgetc(f);

	// Verify that the first character is a digit
	if (!isdigit(ch))
	{
		ungetc(ch, f);
		return (-1);
	}

	// Read digits and build the number
	while (isdigit(ch))
	{
		value = value * 10 + (ch - '0');
		count++;
		ch = fgetc(f);
	}

	// Return last non-digit character
	if (ch != EOF)
		ungetc(ch, f);
	
	if (count == 0)
		return (-1);
	
	*ip = value * sign;
	return (1);
}

// Function to read a string (%s)
int	scan_string(FILE *f, va_list ap)
{
    /*
    * CONVERSION %s:
    * - Skip initial whitespace
    * - Read characters until whitespace is found
    * - Terminate the string with '0'
    * - Push the trailing whitespace character back to the stream
    */
	int	ch = fgetc(f);
	char *sp = va_arg(ap, char *);
	int	i = 0;
	
	// Skip leading spaces
	while (ch != EOF && isspace(ch))
		ch = fgetc(f);

	if (ch == EOF)
		return (-1);

	// Read characters up to a space
	do
	{
		sp[i] = ch;
		i++;
		ch = fgetc(f);
	} while (ch != EOF && !isspace(ch));

	sp[i] = '\0'; // Terminate string

	// Return a space character to the stream
	if (ch != EOF)
		ungetc(ch, f);

	if (i == 0)
		return (-1);
	return (1);
}

// Function to handle format conversions
int	match_conv(FILE *f, const char **format, va_list ap)
{
    /*
    * CONVERSION DISPATCHER:
    * - Inspect the conversion character
    * - Call the appropriate handler function
    * - Handle whitespace for %d and %s automatically
    */
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f); // %d automatically skips spaces
			return scan_int(f, ap);
		case 's':
			match_space(f); // %s automatically skips spaces
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1; // Conversion not supported
	}
}

// Main scanf function
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    /*
     * MAIN SCANF LOGIC:
     * - Parse the format string character by character
     * - Handle literal characters and conversions (%)
     * - Count successful conversions
     * - Stop on the first error
     */
	int nconv = 0; // Number of successful conversions

    // Check that data is available
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
            // Conversion found
			format++;
			if (match_conv(f, &format, ap) != 1)
				break; // Conversion error
			else
				nconv++; // Successful conversion
		}
		else if (isspace(*format))
		{
            // Blank space in format: skip spaces in input
			if (match_space(f) == -1)
				break;
		}
        // Literal character: must match exactly
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	// Check file errors
	if (ferror(f))
		return EOF;
	return nconv; // Return number of successful conversions
}

// Wrapper function for standard scanf
int ft_scanf(const char *format, ...)
{
    /*
     * VARIABLE ARGUMENTS WRAPPER:
     * - Initialize va_list
     * - Call the main function with stdin
     * - Clean up va_list
     */
    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    
    return (ret);
}

int main(void)
{
    int x;
    char str[100];
    char c;

    int converted = ft_scanf("%d %s %c", &x, str, &c);
    
    printf("Converted: %d\n", converted);
    printf("Number: %d, String: %s, Character: %c\n", x, str, c);
    
    return 0;
}

/*
* KEY POINTS FOR THE EXAM:
*
* 1. VARIABLE ARGUMENTS:
* - va_start(ap, last_param) to initialize
* - va_arg(ap, type) to get the next argument
* - va_end(ap) to clean up
*
* 2. FILE FLOW CONTROL:
* - fgetc() to read a character
* - ungetc() to put a character back into the stream
* - ferror() to check for errors
*
* 3. HANDLING SPACES:
* - %c DOES NOT skip whitespace
* - %d and %s DO skip whitespace
* - Spaces in format match any whitespace
*
* 4. RETURN VALUE:
* - Number of successful conversions
* - EOF if file error or EOF before conversions
* - Stops at first failed conversion
*/
