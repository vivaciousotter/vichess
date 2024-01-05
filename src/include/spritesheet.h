#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "piece.h"
#include <memory>
#include <raylib.h>
#include <string>
class Spritesheet {
public:
  Image img;
  Texture2D tex;
  Spritesheet(std::string path);
  Spritesheet &draw(Piece &p, float posX, float posY);
  Rectangle &getWindow(Piece &p);
};
class Sprite {
public:
  std::unique_ptr<Spritesheet> ss;
  Vector2 loc;
  Rectangle window;
  Sprite();
  Sprite(Spritesheet *ss, Vector2 &loc, Rectangle &window);
  Sprite(Spritesheet *ss, Vector2 &loc, Piece &p);
  Sprite &draw();
};
#endif
