#include "include/spritesheet.h"
#include <raylib.h>
#include <string>

Spritesheet::Spritesheet(std::string path) {
  this->img = LoadImage(path.c_str());
  this->tex = LoadTextureFromImage(this->img);
}
Spritesheet &Spritesheet::draw(Piece &p, float posX, float posY) {
  int spriteWidth = this->tex.width / 6;
  int spriteHeight = this->tex.height / 2;
  Rectangle window = {.width = (float)spriteWidth, .height = (float)53};
  Vector2 pos = {.x = posX, .y = posY};
  switch (p.getFlags()) {
  case Piece::White | Piece::King: {
    window.x = 0;
    window.y = 0;
    break;
  }
  case Piece::White | Piece::Queen: {
    window.x = spriteWidth;
    window.y = 0;
    break;
  }
  case Piece::White | Piece::Bishop: {
    window.x = spriteWidth * 2;
    window.y = 0;
    break;
  }
  case Piece::White | Piece::Knight: {
    window.x = spriteWidth * 3;
    window.y = 0;
    break;
  }
  case Piece::White | Piece::Rook: {
    window.x = spriteWidth * 4;
    window.y = 0;
    break;
  }
  case Piece::White | Piece::Pawn: {
    window.x = spriteWidth * 5;
    window.y = 0;
    break;
  }
  case Piece::Black | Piece::King: {
    window.x = 0;
    window.y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Queen: {
    window.x = spriteWidth;
    window.y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Bishop: {
    window.x = spriteWidth * 2;
    window.y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Knight: {
    window.x = spriteWidth * 3;
    window.y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Rook: {
    window.x = spriteWidth * 4;
    window.y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Pawn: {
    window.x = spriteWidth * 5;
    window.y = spriteHeight;
    break;
  }
  default:
    // early return to not draw if the piece doesn't match a phyisical piece
    // type
    return *this;
  }
  DrawTextureRec(this->tex, window, pos, WHITE);
  return *this;
}
