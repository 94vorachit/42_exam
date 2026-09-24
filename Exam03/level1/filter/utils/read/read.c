#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
	// int fd = open("example.txt", O_RDONLY);
	// if (fd < 0) {
	// 	perror("Error opening file");
	// 	return 1;
	// }

	char buffer[100];
	// read up to 99 bytes to leave room for the null terminator
	ssize_t bytesRead = read(0, buffer, sizeof(buffer) - 1); 

	if (bytesRead >= 0) {
		buffer[bytesRead] = '\0'; // Null-terminate the string
		printf("Data read: %s\n", buffer);
	} else {
		perror("Error reading file");
	}

	// close(fd);
	return 0;
}