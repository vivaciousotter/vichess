#include "include/ui.h"
#include <raylib.h>

UI::Board::Board() {
  int bw = -1;
  for (int i = 0; i < 64; i++) {
    this->squares[i].color = bw < 0 ? DARKBROWN : BEIGE;
    this->squares[i].file = i % 8;
    this->squares[i].rank = i / 8;
    this->squares[i].piece = CFlags::None;
    this->tex = LoadTexture("./assets/spritesheet.png");
    if (i % 8 != 7) {
      bw = -bw;
    }
  }
}
void UI::Board::drawAt(int x, int y) {
  for (int i = 0; i < 64; i++) {
    Vector2 loc = {(float)((this->squares[i].file * UI::Square::size) + x),
                   (float)((this->squares[i].rank * UI::Square::size) + y)};
    DrawRectangleV(loc, {(float)UI::Square::size, (float)UI::Square::size},
                   this->squares[i].color);
    if (this->squares[i].piece != CFlags::None) {
      int spriteWidth = this->tex.width / 6;
      int spriteHeight = this->tex.height / 2;
      Rectangle window;
      window.width = (float)spriteWidth;
      window.height = (float)spriteHeight;
      switch (this->squares[i].piece) {
      case CFlags::White | CFlags::King:
        window.x = 0;
        window.y = 0;
        break;
      case CFlags::White | CFlags::Queen:
        window.x = spriteWidth;
        window.y = 0;
        break;
      case CFlags::White | CFlags::Bishop:
        window.x = spriteWidth * 2;
        window.y = 0;
        break;
      case CFlags::White | CFlags::Knight:
        window.x = spriteWidth * 3;
        window.y = 0;
        break;
      case CFlags::White | CFlags::Rook:
        window.x = spriteWidth * 4;
        window.y = 0;
        break;
      case CFlags::White | CFlags::Pawn:
        window.x = spriteWidth * 5;
        window.y = 0;
        break;
      case CFlags::Black | CFlags::King:
        window.x = 0;
        window.y = spriteHeight;
        break;
      case CFlags::Black | CFlags::Queen:
        window.x = spriteWidth;
        window.y = spriteHeight;
        break;
      case CFlags::Black | CFlags::Bishop:
        window.x = spriteWidth * 2;
        window.y = spriteHeight;
        break;
      case CFlags::Black | CFlags::Knight:
        window.x = spriteWidth * 3;
        window.y = spriteHeight;
        break;
      case CFlags::Black | CFlags::Rook:
        window.x = spriteWidth * 4;
        window.y = spriteHeight;
        break;
      case CFlags::Black | CFlags::Pawn:
        window.x = spriteWidth * 5;
        window.y = spriteHeight;
        break;
      default:
        window.x = 0;
        window.y = 0;
        window.width = 0;
        window.height = 0;
      }
      DrawTextureRec(this->tex, window, loc, WHITE);
    }
  }
}
