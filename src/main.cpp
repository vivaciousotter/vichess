#include "include/piece.h"
#include "include/spritesheet.h"
#include <memory>
#include <raylib.h>
#include <string>
// TODO: separate out gui representations

// TODO: Test for proper indexing, using this enum as base
enum class SquareIndex {
  a8,
  a7,
  a6,
  a5,
  a4,
  a3,
  a2,
  a1,
  b8,
  b7,
  b6,
  b5,
  b4,
  b3,
  b2,
  b1,
  c8,
  c7,
  c6,
  c5,
  c4,
  c3,
  c2,
  c1,
  d8,
  d7,
  d6,
  d5,
  d4,
  d3,
  d2,
  d1,
  e8,
  e7,
  e6,
  e5,
  e4,
  e3,
  e2,
  e1,
  f8,
  f7,
  f6,
  f5,
  f4,
  f3,
  f2,
  f1,
  g8,
  g7,
  g6,
  g5,
  g4,
  g3,
  g2,
  g1,
  h8,
  h7,
  h6,
  h5,
  h4,
  h3,
  h2,
  h1
};

typedef unsigned long bb;

std::string files = "abcdefgh";
std::string ranks = "87654321";
std::string startingFEN =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Board;
class Square;
class Position;
// Represents either a physical piece on the board or any comparable
// game trait, such as castling rights that can be represented as
// pieces.
// Represents only a physical square on the board, used mainly for display
// purposes
class Square {
public:
  const static int size = 64;
  Square() {}
  bb bitboardMask() { return 1 << (this->rank + (this->file * 8)); }
  Square(int rank, int file, Color color) {
    this->rank = rank;
    this->file = file;
    this->color = color;
    this->piece = Piece(Piece::None);
  }
  Square(int rank, int file, Color color, Piece piece)
      : Square(rank, file, color) {
    this->piece = piece;
  }
  Square(int rank, int file, Color color, int piece)
      : Square(rank, file, color) {
    this->piece = Piece(piece);
  }
  Square operator=(Square other) {
    this->color = other.color;
    this->rank = other.rank;
    this->file = other.file;
    this->piece = other.piece;
    return *this;
  }
  void draw() {
    int posX = this->rank * Square::size;
    int posY = this->file * Square::size;
    DrawRectangle(posX, posY, Square::size, Square::size, this->color);
    DrawText(TextFormat("%c%c", files[this->rank], ranks[this->file]), posX,
             posY, 25, RED);
  }

  Color color;
  int rank;
  int file;
  Piece piece;
};
// Board representation used for calculating moves;
class Position {
public:
  Piece toMove;
  Piece castling;
  std::string enPassant;
  int halfmove;
  int fullmove;

private:
  bb white;
  bb black;
  bb pawn;
  bb knight;
  bb bishop;
  bb rook;
  bb queen;
  bb king;
};

class Board {
public:
  static int index(int rank, int file) { return file + rank * 8; }
  ~Board() { delete this->sheet; }
  Board() {
    this->sheet = new Spritesheet("./assets/spritesheet.png");
    int bw = -1;
    for (int rank = 0; rank < 8; rank++) {
      for (int file = 0; file < 8; file++) {
        b[Board::index(rank, file)] =
            Square(rank, file, bw < 0 ? WHITE : BLACK, Piece::None);
        if (file != 7)
          bw = -bw;
      }
    }
  }
  Board &applyFen(std::string fen) {
    // https://www.chessprogramming.org/Forsyth-Edwards_Notation
    int bi = 0;
    int fenSection = 0;
    for (int i = 0; i < fen.length(); i++) {
      char c = fen[i];
      if (c == ' ') {
        fenSection++;
      } else {
        switch (fenSection) {
        case 0: {
          // board state
          if (c <= '8' && c >= '1') {
            // advance along the board, parse char as int using ascii math
            bi += (c - '0');
          } else {
            // parse the char in Piece class and assign to current square
            this->b[bi].piece = Piece(c);
          }
          break;
        }
        case 1: {
          // side to move
          switch (c) {
          case 'w':
            this->p.toMove = Piece(Piece::White);
            break;
          case 'b':
            this->p.toMove = Piece(Piece::Black);
            break;
          }
          break;
        }
        case 2: {
          // castling
          switch (c) {
          case 'k':
            this->p.castling.setFlags(Piece::King | Piece::Black);
            break;
          case 'K':
            this->p.castling.setFlags(Piece::King | Piece::White);
            break;
          case 'q':
            this->p.castling.setFlags(Piece::Queen | Piece::Black);
            break;
          case 'Q':
            this->p.castling.setFlags(Piece::Queen | Piece::White);
            break;
          }
          break;
        }
        case 3: {
          // TODO: en passant
          this->p.enPassant += c;
          break;
        }
        case 4: {
          // DONE: halfmove clock
          this->p.halfmove = this->p.halfmove * 10 + (c - '0');
          break;
        }
        case 5: {
          // DONE : fullmove counter
          this->p.fullmove = this->p.fullmove * 10 + (c - '0');
          break;
        }
        default: {
          break;
        }
        }
      }
    }
    return *this;
  }
  void draw() {
    for (int i = 0; i < 64; i++) {
      this->b[i].draw();
      if (b[i].piece.getFlags() != Piece::None) {
        Vector2 loc;
        loc.x = this->b[i].file * Square::size;
        loc.y = this->b[i].rank * Square::size;
        Sprite s = Sprite(this->sheet, loc, this->b[i].piece);
        s.draw();
      }
    }
  }

private:
  Square b[64];
  Spritesheet *sheet;
  Position p;
};

int main(int argv, char **argc) {
  const int screenWidth = 8 * Square::size;
  const int screenHeight = 8 * Square::size;
  InitWindow(screenWidth, screenHeight, "chess");
  Board b = Board();
  b.applyFen(startingFEN);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      b.draw();
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
