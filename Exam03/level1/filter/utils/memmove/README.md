`memmove` function in C is a standard library function used to copy a block of memory from one location to another. It is defined in the `<string.h>` header file.

The defining characteristic of `memmove` is that it safely handles overlapping memory regions. If the source and destination memory blocks overlap, `memmove` ensures that the original data is copied correctly without being overwritten prematurely.

```c
#include <string.h>

void *memmove(void *dest, const void *src, size_t n);
```

Parameters & Return Valuedest: 

* `dest` : A pointer to the destination array or memory block where the content will be copied.
* `src` : A pointer to the source block of data to be copied.
* `n` : The total number of bytes to copy.
* `Return Value` : It returns a void* pointer pointing back to the destination (dest).

Code Example: Handling OverlapThe following example demonstrates shifting elements within the same array (a scenario where memcpy would fail).

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "abcdef";

    // Goal: Shift "abc" two positions to the right to make it "abwbcf" -> "abwabc"
    // Source: "abc" (starts at str)
    // Destination: starts at str + 2
    // Number of bytes: 3 ('a', 'b', 'c')
    
    printf("Before: %s\n", str);

    // Using memmove safely handles the overlap
    memmove(str + 2, str, 3);

    printf("After:  %s\n", str); // Outputs: ababcf
    return 0;
}
```