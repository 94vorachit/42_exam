# `ft_scanf`

### Step 1 : Wrapper function for standard scanf

VARIABLE ARGUMENTS WRAPPER:
* Initialize va_list (#include <stdarg.h>)
* Call the main function with stdin
* Clean up va_list
``` c
int ft_scanf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    
    return (ret);
}
```

### Step 2 : Initialize sub-function in ft_vfscanf

Used functions :
1. match_conv
2. match_space
3. match_char

``` c
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
```

#### Step 2.1 : match_conv

Used functions :
1. scan_char
2. scan_int
3. scan_string

``` c
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
```

#### Step 2.1.1 : Scan_char

Function to read a character (%c)

CONVERSION (%c) :
* Read exactly one character
* Do not skip whitespace
* Store it into the provided pointer

``` c
int	scan_char(FILE *f, va_list ap)
{
	int	ch = fgetc(f);
	char *cp = va_arg(ap, char *);
	if (ch == EOF)
		return (-1);
	*cp = (char)ch;
	return (1);
}
```
#### Step 2.1.2 : Scan_int

Function to read an integer (%d)

CONVERSION (%d) :
* Skip initial whitespace
* Read optional sign (+/-)
* Read digits and build the number
* Push the last non-digit character back to the stream

``` c
int	scan_int(FILE *f, va_list ap)
{
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
```
#### Step 2.1.3 : Scan_string

Function to read a string (%s)

CONVERSION (%s) :
* Skip initial whitespace
* Read characters until whitespace is found
* Terminate the string with '\0'
* Push the trailing whitespace character back to the stream

``` c
int	scan_string(FILE *f, va_list ap)
{
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
```
#### Step 2.2 : match_space

WHITESPACE HANDLING :
* Read characters while they are spaces
* Return the first non-space character to the stream
* Return -1 in case of error

``` c
int	match_space(FILE *f)
{
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
```

#### Step 2.3 : match_char

LITERAL CHARACTER MATCHING :
* Read a character from the stream
* Check if it matches the expected one
* Push it back to the stream if it does not match

``` c
int	match_char(FILE *f, char c)
{
	int	ch = fgetc(f);
	if (ch == c)
		return (1);
	if (ch != EOF)
		ungetc(ch, f);
	return (-1);
}
```

# `Additional`
## `fgetc()`
File handling is one of the most essential features of the C programming language, enabling programs to store, read, and manipulate data stored in files. Two of the simplest yet most commonly used functions for character-level file operations are fgetc() and fputc(). These functions allow you to read from and write to files one character at a time, making them ideal for parsing text, copying files, or performing low-level file operations.

### fgetc(): Reading a Character from a File
fgetc() is used to read a single character at a time from a file.
* It returns the ASCII value of the character read. 
* After reading, the file pointer moves to the next character automatically.
* When the end of the file is reached or if an error occurs, the function returns EOF.
### Syntax:
``` 
int fgetc(FILE *stream)
```
### Parameter: stream
* A pointer to a FILE object that identifies the input stream. This stream is usually obtained by opening a file using the fopen function.

### Return Value : 
* The function returns the character read from the stream as an unsigned char cast to an int.If the end-of-file is encountered or an error occurs, the function returns EOF, which is a macro typically defined as -1. To distinguish between an actual character and an EOF return, one should use the feof or ferror functions to check if the end of the file or an error has occurred.

### How fgetc() Works:
* Reads the character at the current file pointer position.
* Moves the pointer to the next character.
* Continues until EOF.
``` 
Important Notes About EOF:

EOF is not a character, it is a constant defined as -1 in <stdio.h>.
The value -1 helps differentiate between valid characters (ASCII 0–255) and the "end of file" / error state.
``` 

## `fgetc()`
### fputc(): Writing a Character to a File
fputc() writes a single character to a file.
* The file pointer determines where the character will be written.
* After writing, the pointer automatically moves to the next position.
* If the write is successful, the function returns the character written.
* If an error occurs, it returns EOF.
### Syntax:
``` 
int fputc(int char, FILE *pointer)
```
### Parameters:
* char → The character to write (automatically promoted to int).
* pointer → A FILE* to the output stream.
```
When fputc() is executed characters of string variable are written into the file one by one. When we read the line from the file we get the same string that we entered.
```

## `ungetc()`
The ungetc() function takes a single character and shoves it back onto an input stream. It is the opposite of the getc() function, which reads a single character from an input stream. Also, ungetc() is an input function, not an output function. 

### Syntax:
``` 
int ungetc(int char, FILE *stream)
```
### Parameters:
* `char`: specifies the int promotion of the character to be put back. The value is internally converted to an unsigned char when put back.
* `stream`: specifies the pointer to a FILE object that identifies an input stream.
### Return Value: 
The function returns two kind of values.
* On success, the ungetc() function returns the character ch.
* On failure, EOF is returned without changing the stream.
### Important points about the function:
1. The ungetc() function pushes the byte specified by char (converted to an unsigned char) back onto the input stream pointed to by stream.
2. The pushed-back bytes is returned by subsequent reads on that stream in the reverse order of their pushing.
3. A successful intervening call (with the stream pointed to by stream) to a file-positioning function ( fseek(), fsetpos(), or rewind()) discards any pushed-back bytes for the stream.
4. The external storage corresponding to the stream shall be unchanged.
5. A successful call to ungetc() clears the end-of-file indicator for the stream.
6. The value of the file-position indicator for the stream after reading or discarding all pushed-back bytes shall be the same as it was before the bytes were pushed back.
7. The file-position indicator is decremented by each successful call to ungetc(), if its value was 0 before a call, its value is unspecified after the call.

## `ferror()`
In C, ferror() is a built-in function used to check errors in files during file operations. It provides a simple way to do file operations without any interruption in your C program.
### Syntax:
ferror() is a standard library function defined in <stdio.h> file.
``` 
ferror(fptr)
```
### Parameters:
* Take as a file stream in parameter.
### Return Value:
* If the file has error, it returns a non-zero value.
* Otherwise, it returns 0.
```
Note: To check error in file using ferror(), file must be open before it.
```

## `feof()`
The feof() function is used to check whether the file pointer to a stream is pointing to the end of the file or not. It returns a non-zero value if the end is reached, otherwise, it returns 0.
### Syntax:
``` 
feof(fptr);
```
### Parameters:
* fptr: Pointer to a file stream to read the data from.
### Return Value:
* Returns a non-zero value (usually 1) if the end of the file is reached.
* Otherwise, it returns 0.

``` 
Why feof() is needed?
getc() returns the End of File (EOF) when the end of the file is reached. getc() also returns EOF when it fails. So, only comparing the value returned by getc() with EOF is not sufficient to check for the actual end of the file. To solve this problem, C provides feof(). Example:
```