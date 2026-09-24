The ungetc() function in C pushes a character back onto an input stream so that it can be read again by the next read operation. It effectively "undoes" a character read without modifying the actual file or external storage device.

### Syntax and Parameters

```c
#include <stdio.h>
int ungetc(int ch, FILE *stream);
```

* `ch`: The character to be pushed back. It is internally converted to an unsigned char. You cannot push back EOF.
* `stream`: A pointer to the FILE stream (such as stdin or a file handler) where the character will be placed.
* `Return Value`: Returns the pushed character on success, or `EOF` if the operation fails.

### Code Example

The following example reads integers from a string/stream and puts the first non-digit character back:

```c
#include <stdio.h>
#include <ctype.h>

int main(void) {
    int ch;

    printf("Enter some digits followed by letters (e.g., 123xyz): ");

    // 1. Read all consecutive digits
    while ((ch = getchar()) != EOF && isdigit(ch)) {
        putchar(ch); 
    }

    // 2. We hit a non-digit character. Put it back into the stream!
    if (ch != EOF) {
        ungetc(ch, stdin);
    }

    // 3. The next read operation will pick up exactly where we left off
    printf("\nThe next character remaining in the stream is: '%c'\n", getchar());

    return 0;
}
```