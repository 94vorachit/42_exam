NOTE : 
man 3 memmove
man 3 read
man 3 perror

1. 
```c
int	main(int ac, char **av)
{
	/*
	* ARGUMENT VALIDATION:
	* - There must be exactly 1 argument
	* - The argument cannot be empty
	*/
	if (ac != 2)
		return (1);
}
```

2.
```c
#define BUFFER_SIZE 42
#include <unistd.h> // ssize_t, read, write
#include <string.h> // memmove, strlen
#include <stdlib.h> // perror
#include <stdio.h> // realloc, free

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	
	/*
	* DYNAMIC READING FROM STDIN:
	* - Use a temporary buffer to read chunks
	* - Use realloc() to expand the main buffer
	* - Keep track of the total read
	*/
	char temp[BUFFER_SIZE];
	char *result = NULL
	char *buffer;
	size_t	total_read = 0;
	ssize_t	bytes;
}
```

3.
```c
int	main(int ac, char **av)
{
	....
	// Read from stdin until EOF
	// ssize_t read(int fd, void *buf, size_t count);
	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		// Expand the main buffer to accommodate the new data
		// void *realloc(void *ptr, size_t size);
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(buffer);
			perror("realloc");
			return (1);
		}

		result = buffer;

		// Copy the new data to the main buffer
		// void *memmove(void *dest, const void *src, size_t n);
		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0'; // Ensure completion
	}
}
```

4.
```c
int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	
	char	*temp[BEFFER_SIZE];
	char	*result = NULL;
	char	*buffer;
	size_t	total_read = 0;
	ssize_t	bytes;

	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(buffer);
			perror("realloc");
			return (1);
		}

		result = buffer;
		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0'
	}

	// Check for reading errors
	if (bytes < 0)
	{
		free(result);
		perror("read");
		return (0);
	}

	// If nothing was read, exit without error
	if (!result)
		return (0);
	
	free(result);
	return (0);
}
```

5.
```c
void	ft_filter(char *buf, char *tar)
{
	int	i = 0;
	int	tar_len = strlen(tar);

	while(buf[i])
	{
		int	j = 0;
		while (tar[j] && buf[i + j] == tar[j])
			j++;
		if (j == tar_len)
		{
			int	k = 0;
			while (k++ < tar_len)
				write(1, "*", 1);
			i += tar_len
		}
		else
			write(1, &buf[i++], 1);
	}
}

int	main(int ac, char **av)
{
	....
	ft_filter(result, av[1]);
	free(result);
	return (0);
}
```