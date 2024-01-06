#include "include/flags.h"
cflags CFlags::fromChar(char c) {
  cflags flags;
  flags = CFlags::Black;
  switch (c) {
  case 'K':
    flags = CFlags::White;
  case 'k':
    flags |= CFlags::King;
    break;
  case 'Q':
    flags = CFlags::White;
  case 'q':
    flags |= CFlags::Queen;
    break;
  case 'R':
    flags = CFlags::White;
  case 'r':
    flags |= CFlags::Rook;
    break;
  case 'B':
    flags = CFlags::White;
  case 'b':
    flags |= CFlags::Bishop;
    break;
  case 'N':
    flags = CFlags::White;
  case 'n':
    flags |= CFlags::Knight;
    break;
  case 'P':
    flags = CFlags::White;
  case 'p':
    flags |= CFlags::Pawn;
    break;
  default:
    flags = CFlags::None;
    break;
  }
  return flags;
}
cflags CFlags::fromString(std::string s) {
  cflags flags = CFlags::None;
  for (int i = 0; i < s.length(); i++) {
    flags |= CFlags::fromChar(s[i]);
  }
  return flags;
}
