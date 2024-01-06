#ifndef BITBOARD_H
#define BITBOARD_H

typedef unsigned long bitboard;

class Position {
public:
  bitboard pawns, knights, bishops, rooks, queens, kings, white, black;
};

#endif
