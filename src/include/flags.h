#ifndef CHESS_FLAGS_H
#define CHESS_FLAGS_H
#include <string>
typedef unsigned int cflags;

// name
namespace CFlags {
enum CFlags : cflags {
  None = 0,
  Pawn = 1,
  Knight = 1 << 1,
  Bishop = 1 << 2,
  Rook = 1 << 3,
  Queen = 1 << 4,
  King = 1 << 5,
  White = 1 << 6,
  Black = 1 << 7
};
cflags fromChar(char c);
cflags fromString(std::string s);
class HasFlags {
protected:
  cflags flags;

public:
  cflags getFlags();
  void replaceFlags(cflags flags);
  void setFlags(cflags flags);
  void unsetFlags(cflags flags);
  void clearFlags();
  void applyMask(cflags mask);
};
} // namespace CFlags

#endif
