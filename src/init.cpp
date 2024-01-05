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
class Piece;
class Square;
class Position;
// Represents either a physical piece on the board or any comparable
// game trait, such as castling rights that can be represented as
// pieces.
class Piece {
public:
  const static unsigned short None = 0, Black = 128, White = 64, Pawn = 1,
                              Knight = 2, Bishop = 4, Rook = 8, Queen = 16,
                              King = 32;
  Piece() {}
  Piece(int color, int type) { this->flags = color | type; }
  Piece(int flags) { this->flags = flags; }
  Piece(char c) {
    this->flags = Piece::None;
    if (c <= 'Z' && c >= 'A') {
      this->flags |= Piece::White;
    } else if (c <= 'z' && c >= 'a') {
      this->flags |= Piece::Black;
    }
    switch (c) {
    case 'K':
    case 'k':
      this->flags |= Piece::King;
      break;
    case 'Q':
    case 'q':
      this->flags |= Piece::Queen;
      break;
    case 'R':
    case 'r':
      this->flags |= Piece::Rook;
      break;
    case 'B':
    case 'b':
      this->flags |= Piece::Bishop;
      break;
    case 'N':
    case 'n':
      this->flags |= Piece::Knight;
      break;
    case 'P':
    case 'p':
      this->flags |= Piece::Pawn;
      break;
    default:
      this->flags = Piece::None;
      break;
    }
  }
  Piece &setFlags(int flags) {
    this->flags |= flags;
    return *this;
  }
  Piece &unsetFlags(int flags) {
    this->flags &= ~flags;
    return *this;
  }
  Piece &operator=(const Piece &other) {
    this->flags = other.flags;
    return *this;
  }
  bool operator==(const Piece &other) { return this->flags == other.flags; }
  bool operator==(unsigned int other) { return this->flags == other; }
  bool operator==(unsigned short other) { return this->flags == other; }
  bool operator==(int other) { return this->flags == other; }
  bool operator==(short other) { return this->flags == other; }
  bool operator!=(const Piece &other) { return this->flags != other.flags; }
  unsigned int getFlags() { return this->flags; }

private:
  unsigned int flags;
};
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

class Spritesheet {
public:
  Image img;
  Texture2D tex;
  Spritesheet(std::string path) {
    this->img = LoadImage(path.c_str());
    this->tex = LoadTextureFromImage(this->img);
  }
  Spritesheet &draw(Piece &p, float posX, float posY) {
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
};
class Board {
public:
  static int index(int rank, int file) { return file + rank * 8; }
  Board() {
    this->sheet =
        std::make_unique<Spritesheet>(Spritesheet("./assets/spritesheet.png"));
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
      int posX = this->b[i].file * Square::size;
      int posY = this->b[i].rank * Square::size;
      this->sheet->draw(this->b[i].piece, posX, posY);
    }
  }

private:
  Square b[64];
  std::unique_ptr<Spritesheet> sheet;
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
