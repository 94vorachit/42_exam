#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    
    char *line;
    int line_count = 0;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        size_t	len;

        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            len--;
        printf("Line %d: [%.*s]\n", ++line_count, (int)len, line);
        free(line);
    }
    
    printf("Total lines read: %d\n", line_count);
    close(fd);
    return 0;
}
