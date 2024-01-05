#ifndef PIECE_H
#define PIECE_H
class Piece {
public:
  const static unsigned short None = 0, Black = 128, White = 64, Pawn = 1,
                              Knight = 2, Bishop = 4, Rook = 8, Queen = 16,
                              King = 32;
  Piece();
  Piece(int color, int type);
  Piece(int flags);
  Piece(char c);
  Piece &setFlags(int flags);
  Piece &unsetFlags(int flags);
  Piece &operator=(const Piece &other);
  bool operator==(const Piece &other);
  bool operator==(unsigned int other);
  bool operator==(unsigned short other);
  bool operator==(int other);
  bool operator==(short other);
  bool operator!=(const Piece &other);
  unsigned int getFlags();

private:
  unsigned int flags;
};
#endif
