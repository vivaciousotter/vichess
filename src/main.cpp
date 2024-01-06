#include "include/position.h"
#include "include/ui.h"
#include <raylib.h>
// TODO: separate out gui representations

int main(int argv, char **argc) {
  const int screenWidth = 8 * UI::Square::size;
  const int screenHeight = 8 * UI::Square::size;
  InitWindow(screenWidth, screenHeight, "chess");
  UI::Board board;
  Position p;
  for (int i = 0; i < 64; i++) {
    board.squares[i].piece = p.squares[i];
  }
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      board.drawAt(0, 0);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
