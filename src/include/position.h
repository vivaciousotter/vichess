#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "flags.h"
#include <array>
#include <cstdint>
#include <memory>

namespace Piece {
using enum CFlags::CFlags;
}

namespace Player {
enum { White = CFlags::White, Black = CFlags::Black };
}

// namespaced enum so it coerces to an int for easy indexing
namespace Square {
enum {
  // clang-format off
  a8, b8, c8, d8, e8, f8, g8, h8,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a1, b1, c1, d1, e1, f1, g1, h1,
  // clang-format on
};
std::string fromInt(int i);
} // namespace Square

// namespace for precomputed bitboards and helper function
namespace BitBoard {
typedef uint64_t bb;
const bb aRank = 0xFF00000000000000;
const bb bRank = aRank >> 8;
const bb cRank = bRank >> 8;
const bb dRank = cRank >> 8;
const bb eRank = dRank >> 8;
const bb fRank = eRank >> 8;
const bb gRank = fRank >> 8;
const bb hRank = gRank >> 8;
const bb ranks[8] = {aRank, bRank, cRank, dRank, eRank, fRank, gRank, hRank};
// clang-format off
const bb oneFile   = 0x0101010101010101;
const bb twoFile   = oneFile   << 1;
const bb threeFile = twoFile   << 1;
const bb fourFile  = threeFile << 1;
const bb fiveFile  = fourFile  << 1;
const bb sixFile   = fiveFile  << 1;
const bb sevenFile = sixFile   << 1;
const bb eightFile = sevenFile << 1;
// clang-format on
const bb files[8] = {eightFile, sevenFile, sixFile, fiveFile,
                     fourFile,  threeFile, twoFile, oneFile};
// clang-format off
// Squares indexed by Square::{algnotation} ie BitBoard::squares[Squares::a1] returns a bitmask for a1
const bb squares[64] = { 
  ranks[0]&files[0], ranks[0]&files[1], ranks[0]&files[2], ranks[0]&files[3], ranks[0]&files[4], ranks[0]&files[5], ranks[0]&files[6], ranks[0]&files[7],
  ranks[1]&files[0], ranks[1]&files[1], ranks[1]&files[2], ranks[1]&files[3], ranks[1]&files[4], ranks[1]&files[5], ranks[1]&files[6], ranks[1]&files[7],
  ranks[2]&files[0], ranks[2]&files[1], ranks[2]&files[2], ranks[2]&files[3], ranks[2]&files[4], ranks[2]&files[5], ranks[2]&files[6], ranks[2]&files[7],
  ranks[3]&files[0], ranks[3]&files[1], ranks[3]&files[2], ranks[3]&files[3], ranks[3]&files[4], ranks[3]&files[5], ranks[3]&files[6], ranks[3]&files[7],
  ranks[4]&files[0], ranks[4]&files[1], ranks[4]&files[2], ranks[4]&files[3], ranks[4]&files[4], ranks[4]&files[5], ranks[4]&files[6], ranks[4]&files[7],
  ranks[5]&files[0], ranks[5]&files[1], ranks[5]&files[2], ranks[5]&files[3], ranks[5]&files[4], ranks[5]&files[5], ranks[5]&files[6], ranks[5]&files[7],
  ranks[6]&files[0], ranks[6]&files[1], ranks[6]&files[2], ranks[6]&files[3], ranks[6]&files[4], ranks[6]&files[5], ranks[6]&files[6], ranks[6]&files[7],
  ranks[7]&files[0], ranks[7]&files[1], ranks[7]&files[2], ranks[7]&files[3], ranks[7]&files[4], ranks[7]&files[5], ranks[7]&files[6], ranks[7]&files[7]
};
// clang-format on
} // namespace BitBoard

class Position {
public:
  Position();
  cflags squares[64];

private:
  cflags whiteCastle;
  cflags blackCastle;
  cflags toMove;
  int halfmove;
  int fullmove;
};

#endif
