#ifndef PIECES_H
#define PIECES_H

#define MAX_PIECES 100

typedef struct {
    int length;
    int price;
    int max_usage;  // ExtraPoint: Maximum times this piece can be used (0 = unlimited)
} Piece;


#endif
