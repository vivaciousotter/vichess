#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "piece.h"
#include <raylib.h>
#include <string>
class Spritesheet {
public:
  Image img;
  Texture2D tex;
  Spritesheet(std::string path);
  Spritesheet &draw(Piece &p, float posX, float posY);
};
#endif
