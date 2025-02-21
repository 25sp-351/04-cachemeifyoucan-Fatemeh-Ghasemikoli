#include "solution.h"  
#include "rodcutting.h"
#include <stdio.h>
#include <stdlib.h>

void calc_rod_cutting(Piece pieces[], int count, int rod_length) { // Solve the rod cutting problem
    int *values = (int *)malloc((rod_length + 1) * sizeof(int)); // Tracks the best value for each length
    int *cuts   = (int *)malloc((rod_length + 1) * sizeof(int)); // Tracks the best piece for each length
    int *usage_tracker = (int *)malloc(count * sizeof(int));     // Tracks piece usage

    if (values == NULL || cuts == NULL || usage_tracker == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize arrays
    for (int currentLength = 0; currentLength <= rod_length; currentLength++) {
        values[currentLength] = 0;
        cuts[currentLength]   = -1;
    }
    
    for (int i = 0; i < count; i++) {
        usage_tracker[i] = 0;  // Reset usage for each piece
    }

    // Calculate the best value for each length
    for (int currentLength = 1; currentLength <= rod_length; currentLength++) {
        for (int pieceIndex = 0; pieceIndex < count; pieceIndex++) {
            if (pieces[pieceIndex].length <= currentLength) {

                int occurrences = 0;
                int tempLength = currentLength - pieces[pieceIndex].length;
                
                while (tempLength > 0 && cuts[tempLength] == pieceIndex) {
                    occurrences++;
                    tempLength -= pieces[pieceIndex].length;
                }

                // Check if we can use this piece (max_usage = 0 means unlimited)
                if (pieces[pieceIndex].max_usage == 0 || occurrences < pieces[pieceIndex].max_usage) {
                    int newValue = pieces[pieceIndex].price + values[currentLength - pieces[pieceIndex].length];

                    if (newValue > values[currentLength]) {
                        values[currentLength] = newValue;
                        cuts[currentLength]   = pieceIndex;
                    }
                }
            }
        }
    }

    print_solution(rod_length, pieces, cuts, values[rod_length]);

    free(values);
    free(cuts);
    free(usage_tracker);
}
