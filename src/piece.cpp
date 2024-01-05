#include "include/piece.h"
Piece::Piece(){};

Piece::Piece(int color, int type) { this->flags = color | type; }

Piece::Piece(int flags) { this->flags = flags; }

Piece::Piece(char c) {
  this->flags = Piece::None;
  if (c <= 'Z' && c >= 'A') {
    this->flags |= Piece::White;
  } else if (c <= 'z' && c >= 'a') {
    this->flags |= Piece::Black;
  }
  switch (c) {
  case 'K':
  case 'k':
    this->flags |= Piece::King;
    break;
  case 'Q':
  case 'q':
    this->flags |= Piece::Queen;
    break;
  case 'R':
  case 'r':
    this->flags |= Piece::Rook;
    break;
  case 'B':
  case 'b':
    this->flags |= Piece::Bishop;
    break;
  case 'N':
  case 'n':
    this->flags |= Piece::Knight;
    break;
  case 'P':
  case 'p':
    this->flags |= Piece::Pawn;
    break;
  default:
    this->flags = Piece::None;
    break;
  }
}
Piece &Piece::setFlags(int flags) {
  this->flags |= flags;
  return *this;
}
Piece &Piece::unsetFlags(int flags) {
  this->flags &= ~flags;
  return *this;
}
Piece &Piece::operator=(const Piece &other) {
  this->flags = other.flags;
  return *this;
}
bool Piece::operator==(const Piece &other) {
  return this->flags == other.flags;
}
bool Piece::operator==(unsigned int other) { return this->flags == other; }
bool Piece::operator==(unsigned short other) { return this->flags == other; }
bool Piece::operator==(int other) { return this->flags == other; }
bool Piece::operator==(short other) { return this->flags == other; }
bool Piece::operator!=(const Piece &other) {
  return this->flags != other.flags;
}
unsigned int Piece::getFlags() { return this->flags; }
