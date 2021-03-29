#include "Move.h"
#include "BitboardHelper.h"

Move::Move() {
}

Move::Move(int bi, int numOfPieces, std::uint64_t toFlip, double score) : bi(bi), numOfPieces(numOfPieces), toFlip(toFlip), score(score) {
}
