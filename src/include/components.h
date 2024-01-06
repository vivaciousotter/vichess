#ifndef CHESS_UI_H
#define CHESS_UI_H
#include <raylib.h>
class Component {
public:
  virtual void draw(Vector2 loc);
  virtual void draw(int x, int y);
  Rectangle boundingBox;
};

class PieceTexture {
public:
private:
  Texture2D tex;
};

class BoardComponent : Component {};
class SquareComponent : Component {};
class PieceComponent : Component {};
#endif
