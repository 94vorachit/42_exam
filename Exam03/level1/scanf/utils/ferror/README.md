The `ferror` function in C checks for internal errors on a given file stream. Defined in the `<stdio.h>` header, it tests the internal error indicator of a file stream that may have been tripped during read or write operations.

### Syntax

```c
int ferror(FILE *stream);
```

### Return Values
* `0`: No error has occurred on the stream.
* `Non-zero value`: An error has occurred during a file operation.

### Code Example

The following example demonstrates how to check if a file read failed due to reaching the end of the file or because an actual I/O error occurred:

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Attempting an invalid operation: writing to a read-only file stream
    fputc('A', file); 

    // Check if the write operation triggered a stream error
    if (ferror(file)) {
        printf("A stream error was detected!\n");
        
        // Print the system-level error reason
        perror("Reason for error"); 
        
        // Reset the stream indicators if you intend to keep using the file
        clearerr(file); 
    }

    fclose(file);
    return 0;
}
```