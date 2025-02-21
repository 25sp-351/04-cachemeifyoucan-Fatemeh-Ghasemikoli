#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pieces.h"
#include "rodcutting.h"
#include "input.h"

#define MAX_INPUT_SIZE 100  // Buffer size for input

int main(int argc, char *argv[]) { // Main function
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pieces_file>\n", argv[0]);
        return 1;
    }

    // Read pieces from the file
    Piece pieces[MAX_PIECES];
    int pieceCount = 0;
    if (read_input(argv[1], pieces, &pieceCount) != 0) {
        fprintf(stderr, "Error reading pieces.\n");
        return 1;
    }

    // Read rod lengths from stdin (one per line) until EOF
    char input[MAX_INPUT_SIZE];
    printf("Enter rod lengths, one per line. Ctrl+C to exit.\n");

    while (fgets(input, sizeof(input), stdin)) {
        // Remove trailing newline if present
        input[strcspn(input, "\n")] = '\0';

        // Trim leading and trailing spaces
        char *trimmed = strtok(input, " "); // Get first token (ignoring leading spaces)

        // Check if input is empty
        if (trimmed == NULL) {
            printf("Error: Input cannot be empty.\n");
            continue;
        }

        // Validate input: Ensure all characters are digits
        int valid = 1;
        for (int i = 0; trimmed[i] != '\0'; i++) {
            if (!isdigit(trimmed[i])) {  // Check if each character is a digit
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Error: Invalid input. Please enter a positive integer.\n");
            continue;
        }

        // Convert input manually
        long rod_length = 0;
        char *ptr = trimmed;
        while (*ptr) {
            rod_length = rod_length * 10 + (*ptr - '0'); // Convert char to int
            ptr++;
        }

        // Ensure it's not negative or zero
        if (rod_length <= 0) {
            printf("Error: Rod length must be a positive integer.\n");
            continue;
        }

        // Ensure it's within a reasonable range
        if (rod_length > 100000) {
            printf("Error: Rod length is too large.\n");
            continue;
        }

        // Process the valid rod length
        calc_rod_cutting(pieces, pieceCount, (int)rod_length);
        printf("\n");
    }

    return 0;
}
