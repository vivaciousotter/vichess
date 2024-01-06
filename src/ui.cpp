#include "include/ui.h"
#include <raylib.h>
// set up some default drawing behavior
void Component::draw() { this->drawAt(0, 0); }
void Component::drawAt(Vector2 loc) { this->drawAt(loc.x, loc.y); }
void Component::drawAt(int x, int y) { DrawRectangle(x, y, 200, 200, RED); }

// BoardComponent constructor, setting up the array of SquareComponents
BoardComponent::BoardComponent() {
  int bw = -1;
  for (int i = 0; i < 64; i++) {
    this->squares[i].color = bw < 0 ? DARKBROWN : BEIGE;
    this->squares[i].file = i % 8;
    this->squares[i].rank = i / 8;
    if (this->squares[i].rank == 1) {
      this->squares[i].piece =
          std::make_unique<PieceComponent>(PieceComponent('P'));
    }
    if (this->squares[i].rank == 6) {
      this->squares[i].piece =
          std::make_unique<PieceComponent>(PieceComponent('p'));
    }
    if (i % 8 != 7) {
      bw = -bw;
    }
  }
  this->boundingBox.width = 8 * SquareComponent::size;
  this->boundingBox.height = 8 * SquareComponent::size;
}
void BoardComponent::drawAt(int x, int y) {
  for (int i = 0; i < 64; i++) {
    this->squares[i].drawAt(x, y);
  }
  this->boundingBox.x = x;
  this->boundingBox.y = y;
}
SquareComponent &BoardComponent::operator[](int i) { return this->squares[i]; }

void SquareComponent::drawAt(int x, int y) {
  Vector2 loc = {(float)((this->file * this->size) + x),
                 (float)((this->rank * this->size) + y)};
  DrawRectangleV(loc, {(float)this->size, (float)this->size}, this->color);
  this->boundingBox.x = x;
  this->boundingBox.y = y;
  this->boundingBox.width = this->size;
  this->boundingBox.height = this->size;
  if (this->piece) {
    this->piece->drawAt(loc.x, loc.y);
  }
}

PieceComponent::PieceComponent() {
  this->piece = CFlags::None;
  this->tex = LoadTexture("./assets/spritesheet.png");
}
PieceComponent::PieceComponent(char c) {
  this->piece = CFlags::fromChar(c);
  this->tex = LoadTexture("./assets/spritesheet.png");
}
void PieceComponent::setPiece(char c) { this->piece = CFlags::fromChar(c); }
void PieceComponent::drawAt(int x, int y) {
  int spriteWidth = this->tex.width / 6;
  int spriteHeight = this->tex.height / 2;
  Rectangle window;
  window.width = (float)spriteWidth;
  window.height = (float)spriteHeight;
  switch (this->piece) {
  case CFlags::White | CFlags::King: {
    window.x = 0;
    window.y = 0;
    break;
  }
  case CFlags::White | CFlags::Queen: {
    window.x = spriteWidth;
    window.y = 0;
    break;
  }
  case CFlags::White | CFlags::Bishop: {
    window.x = spriteWidth * 2;
    window.y = 0;
    break;
  }
  case CFlags::White | CFlags::Knight: {
    window.x = spriteWidth * 3;
    window.y = 0;
    break;
  }
  case CFlags::White | CFlags::Rook: {
    window.x = spriteWidth * 4;
    window.y = 0;
    break;
  }
  case CFlags::White | CFlags::Pawn: {
    window.x = spriteWidth * 5;
    window.y = 0;
    break;
  }
  case CFlags::Black | CFlags::King: {
    window.x = 0;
    window.y = spriteHeight;
    break;
  }
  case CFlags::Black | CFlags::Queen: {
    window.x = spriteWidth;
    window.y = spriteHeight;
    break;
  }
  case CFlags::Black | CFlags::Bishop: {
    window.x = spriteWidth * 2;
    window.y = spriteHeight;
    break;
  }
  case CFlags::Black | CFlags::Knight: {
    window.x = spriteWidth * 3;
    window.y = spriteHeight;
    break;
  }
  case CFlags::Black | CFlags::Rook: {
    window.x = spriteWidth * 4;
    window.y = spriteHeight;
    break;
  }
  case CFlags::Black | CFlags::Pawn: {
    window.x = spriteWidth * 5;
    window.y = spriteHeight;
    break;
  }
  default:
    window.x = 0;
    window.y = 0;
    window.width = 0;
    window.height = 0;
  }
  DrawTextureRec(this->tex, window, {(float)x, (float)y}, WHITE);
  // update boundingBox
  this->boundingBox.x = x;
  this->boundingBox.y = y;
  this->boundingBox.width = window.width;
  this->boundingBox.height = window.height;
}
