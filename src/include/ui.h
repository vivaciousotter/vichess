#ifndef CHESS_UI_H
#define CHESS_UI_H
#include "flags.h"
#include "position.h"
#include <memory>
#include <raylib.h>
namespace UI {
class Square {
public:
  static const int size = 64;
  Color color;
  int rank;
  int file;
  cflags piece;
};
class Board {
public:
  Board();
  void drawAt(int x, int y);
  std::array<Square, 64> squares;
  int selectedSquare;

private:
  Texture2D tex;
};
} // namespace UI
#endif
