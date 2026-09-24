The `fgetc()` function in C reads a single character from a specified input stream (such as a file or standard input) and advances the stream's internal position indicator to the next character. It is defined in the `<stdio.h>` header library.

### Syntax

```c
int fgetc(FILE *stream);
```

### Parameters & Return Value

* `stream`: A pointer to a `FILE` object that identifies the stream to read from (e.g., a file opened with `fopen()` or standard input `stdin`).
* `Return Value`: Returns the read character as an `unsigned char` converted to an `int` on success. If the end of the file is reached or a read error occurs, it returns the constant `EOF` (End Of File, typically `-1`).

```
⚠️ Important: You must store the return value of fgetc() in an int variable, not a char. If you use a char, it may not be able to correctly represent or distinguish the EOF flag from a legitimate character value.
```

### Code Example: Reading a File Character by Character

The most common use case for fgetc() is reading through a text file sequentially until the end of the file is met:

```c
#include <stdio.h>

int main() {
    // Open a file in read-only mode ("r")
    FILE *file = fopen("example.txt", "r");
    
    // Check if the file exists and opened successfully
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int ch; // Variable to hold the character; must be int to check for EOF

    // Read characters one by one until EOF is encountered
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); // Print the character to the console
    }

    // Close the file stream
    fclose(file);
    return 0;
}
```