#include "include/position.h"

std::string Square::fromInt(int i) {
  using namespace Square;
  switch (i) {
  case a1:
    return "a1";
  case a2:
    return "a2";
  case a3:
    return "a3";
  case a4:
    return "a4";
  case a5:
    return "a5";
  case a6:
    return "a6";
  case a7:
    return "a7";
  case a8:
    return "a8";
  case b1:
    return "b1";
  case b2:
    return "b2";
  case b3:
    return "b3";
  case b4:
    return "b4";
  case b5:
    return "b5";
  case b6:
    return "b6";
  case b7:
    return "b7";
  case b8:
    return "b8";
  case c1:
    return "c1";
  case c2:
    return "c2";
  case c3:
    return "c3";
  case c4:
    return "c4";
  case c5:
    return "c5";
  case c6:
    return "c6";
  case c7:
    return "c7";
  case c8:
    return "c8";
  case d1:
    return "d1";
  case d2:
    return "d2";
  case d3:
    return "d3";
  case d4:
    return "d4";
  case d5:
    return "d5";
  case d6:
    return "d6";
  case d7:
    return "d7";
  case d8:
    return "d8";
  case e1:
    return "e1";
  case e2:
    return "e2";
  case e3:
    return "e3";
  case e4:
    return "e4";
  case e5:
    return "e5";
  case e6:
    return "e6";
  case e7:
    return "e7";
  case e8:
    return "e8";
  case f1:
    return "f1";
  case f2:
    return "f2";
  case f3:
    return "f3";
  case f4:
    return "f4";
  case f5:
    return "f5";
  case f6:
    return "f6";
  case f7:
    return "f7";
  case f8:
    return "f8";
  case g1:
    return "g1";
  case g2:
    return "g2";
  case g3:
    return "g3";
  case g4:
    return "g4";
  case g5:
    return "g5";
  case g6:
    return "g6";
  case g7:
    return "g7";
  case g8:
    return "g8";
  case h1:
    return "h1";
  case h2:
    return "h2";
  case h3:
    return "h3";
  case h4:
    return "h4";
  case h5:
    return "h5";
  case h6:
    return "h6";
  case h7:
    return "h7";
  case h8:
    return "h8";
  }
  return "";
}

Position::Position() {
  for (int i = 0; i < 64; i++) {
    this->squares[i] = Piece::None;
    if (i == Square::a8 || i == Square::h8) {
      this->squares[i] = (Piece::Black | Piece::Rook);
    } else if (i == Square::b8 || i == Square::g8) {
      this->squares[i] = (Piece::Black | Piece::Knight);
    } else if (i == Square::c8 || i == Square::f8) {
      this->squares[i] = (Piece::Black | Piece::Bishop);
    } else if (i == Square::d8) {
      this->squares[i] = (Piece::Black | Piece::Queen);
    } else if (i == Square::e8) {
      this->squares[i] = (Piece::Black | Piece::King);
    } else if (i > Square::h8 && i < Square::a6) {
      this->squares[i] = (Piece::Black | Piece::Pawn);
    } else if (i == Square::a1 || i == Square::h1) {
      this->squares[i] = (Piece::White | Piece::Rook);
    } else if (i == Square::b1 || i == Square::g1) {
      this->squares[i] = (Piece::White | Piece::Knight);
    } else if (i == Square::c1 || i == Square::f1) {
      this->squares[i] = (Piece::White | Piece::Bishop);
    } else if (i == Square::d1) {
      this->squares[i] = (Piece::White | Piece::Queen);
    } else if (i == Square::e1) {
      this->squares[i] = (Piece::White | Piece::King);
    } else if (i > Square::h3 && i < Square::a1) {
      this->squares[i] = (Piece::White | Piece::Pawn);
    }
  }
};
