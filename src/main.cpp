#include "include/position.h"
#include "include/ui.h"
#include <raylib.h>
// TODO: separate out gui representations

int main(int argv, char **argc) {
  const int screenWidth = 8 * SquareComponent::size;
  const int screenHeight = 8 * SquareComponent::size;
  InitWindow(screenWidth, screenHeight, "chess");
  BoardComponent board;
  Mailbox::Position p;
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
