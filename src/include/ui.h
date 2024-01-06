#ifndef CHESS_UI_H
#define CHESS_UI_H
#include "flags.h"
#include <memory>
#include <raylib.h>

class Component {
public:
  virtual void draw();
  virtual void drawAt(int x, int y);
  virtual void drawAt(Vector2 loc);
  Rectangle boundingBox;
};

class PieceComponent : public Component {
public:
  cflags piece;
  PieceComponent();
  PieceComponent(char c);
  PieceComponent(cflags piece);
  void setPiece(char c);
  void drawAt(int x, int y);

private:
  Texture2D tex;
};
class SquareComponent : public Component {
public:
  const static int size = 64;
  std::unique_ptr<PieceComponent> piece;
  void drawAt(int x, int y);
  Color color;
  int rank;
  int file;
};
class BoardComponent : public Component {
public:
  BoardComponent();
  SquareComponent &operator[](int i);
  void drawAt(int x, int y);

private:
  SquareComponent squares[64];
};
#endif
