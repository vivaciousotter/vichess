#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H
#include "flags.h"
#include <cstdint>

class Piece {
  using enum CFlags::CFflags;
};

// namespaced enum so it coerces to an int for easy indexing
namespace Square {
enum {
  // clang-format off
  a8, a7, a6, a5, a4, a3, a2, a1,
  b8, b7, b6, b5, b4, b3, b2, b1,
  c8, c7, c6, c5, c4, c3, c2, c1,
  d8, d7, d6, d5, d4, d3, d2, d1,
  e8, e7, e6, e5, e4, e3, e2, e1,
  f8, f7, f6, f5, f4, f3, f2, f1,
  g8, g7, g6, g5, g4, g3, g2, g1,
  h8, h7, h6, h5, h4, h3, h2, h1
  // clang-format on
};
}
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
class Position {
public:
  bb pawns, knights, bishops, rooks, queens, kings, white, black;
};
// clang-format on
} // namespace BitBoard

namespace Mailbox {
class Position {
private:
};
} // namespace Mailbox

#endif
