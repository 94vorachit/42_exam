#include <stdio.h>

int main() 
{
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