#include "include/spritesheet.h"
#include <raylib.h>
#include <string>

Spritesheet::Spritesheet(std::string path) {
  this->img = LoadImage(path.c_str());
  this->tex = LoadTextureFromImage(this->img);
}
Rectangle &Spritesheet::getWindow(Piece &p) {
  int spriteWidth = this->tex.width / 6;
  int spriteHeight = this->tex.height / 2;
  Rectangle *window;
  window->width = (float)spriteWidth;
  window->height = (float)53;
  switch (p.getFlags()) {
  case Piece::White | Piece::King: {
    window->x = 0;
    window->y = 0;
    break;
  }
  case Piece::White | Piece::Queen: {
    window->x = spriteWidth;
    window->y = 0;
    break;
  }
  case Piece::White | Piece::Bishop: {
    window->x = spriteWidth * 2;
    window->y = 0;
    break;
  }
  case Piece::White | Piece::Knight: {
    window->x = spriteWidth * 3;
    window->y = 0;
    break;
  }
  case Piece::White | Piece::Rook: {
    window->x = spriteWidth * 4;
    window->y = 0;
    break;
  }
  case Piece::White | Piece::Pawn: {
    window->x = spriteWidth * 5;
    window->y = 0;
    break;
  }
  case Piece::Black | Piece::King: {
    window->x = 0;
    window->y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Queen: {
    window->x = spriteWidth;
    window->y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Bishop: {
    window->x = spriteWidth * 2;
    window->y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Knight: {
    window->x = spriteWidth * 3;
    window->y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Rook: {
    window->x = spriteWidth * 4;
    window->y = spriteHeight;
    break;
  }
  case Piece::Black | Piece::Pawn: {
    window->x = spriteWidth * 5;
    window->y = spriteHeight;
    break;
  }
  default:
    window->x = 0;
    window->y = 0;
    window->width = 0;
    window->height = 0;
  }
  return *window;
};
Spritesheet &Spritesheet::draw(Piece &p, float posX, float posY) {
  int spriteWidth = this->tex.width / 6;
  int spriteHeight = this->tex.height / 2;
  Rectangle window = this->getWindow(p);
  Vector2 pos = {.x = posX, .y = posY};
  DrawTextureRec(this->tex, window, pos, WHITE);
  return *this;
}

Sprite::Sprite() {
  this->ss =
      std::make_unique<Spritesheet>(Spritesheet("../assets/spritesheet.png"));
  this->loc = {0, 0};
  this->window = {0, 0, 0, 0};
}
Sprite::Sprite(Spritesheet *ss, Vector2 &loc, Rectangle &window) {
  this->window = window;
  this->loc = loc;
  this->ss = std::make_unique<Spritesheet>(*ss);
}
Sprite::Sprite(Spritesheet *ss, Vector2 &loc, Piece &p) {
  this->window = ss->getWindow(p);
  this->loc = loc;
  this->ss = std::make_unique<Spritesheet>(*ss);
}
Sprite &Sprite::draw() {
  DrawTextureRec(this->ss->tex, this->window, this->loc, WHITE);
  return *this;
}
