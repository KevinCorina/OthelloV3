#define OPEN_EDGES(p) empty & (p << 8 | p >> 8 | (bbh::NOT_RIGHT_EDGE& (p << 1 | p >> 7 | p << 9)) | (bbh::NOT_LEFT_EDGE & (p >> 1 | p << 7 | p >> 9)));

#include "Color.h"
#include "OthelloBoard.h"
#include "BitboardHelper.h"
#include "CommandLineInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <algorithm>

using namespace std;

OthelloBoard::OthelloBoard() {
	place(bbh::XY_TO_BI[4][3], BLACK);
	place(bbh::XY_TO_BI[3][4], BLACK);
	place(bbh::XY_TO_BI[3][3], WHITE);
	place(bbh::XY_TO_BI[4][4], WHITE);
}

OthelloBoard::OthelloBoard(std::string richString)
{
	std::replace(richString.begin(), richString.end(), '.', '0');
	std::string blackString = richString;
	std::replace(blackString.begin(), blackString.end(), 'B', '1');
	std::replace(blackString.begin(), blackString.end(), 'W', '0');
	std::string whiteString = richString;
	std::replace(whiteString.begin(), whiteString.end(), 'W', '1');
	std::replace(whiteString.begin(), whiteString.end(), 'B', '0');

	
	pieces[BLACK] = bbh::bbFromBinaryString(blackString);
	pieces[WHITE] = bbh::bbFromBinaryString(whiteString);
	numOfPieces[BLACK] = __popcnt64(pieces[BLACK]);
	numOfPieces[WHITE] = __popcnt64(pieces[WHITE]);
	empty = ~pieces[BLACK] & ~pieces[WHITE];

	
}

OthelloBoard::OthelloBoard(const OthelloBoard& ob) {
	std::copy(std::begin(ob.numOfPieces), std::end(ob.numOfPieces), std::begin(numOfPieces));
	std::copy(std::begin(ob.pieces), std::end(ob.pieces), std::begin(pieces));
	empty = ob.empty;

}

OthelloBoard::OthelloBoard(bitboard black, bitboard white) {
	pieces[BLACK] = black;
	pieces[WHITE] = white;
	numOfPieces[BLACK] = __popcnt64(black);
	numOfPieces[WHITE] = __popcnt64(white);
	empty = ~black & ~white;
}

std::string OthelloBoard::toString(bool A1Origin)
{
	char s[3] = { 'B','W','.' };
	std::uint64_t b[3] = { pieces[BLACK], pieces[WHITE], empty };
	return bbh::bitBoardToString(b, 3, true, "BW.");
}

bool OthelloBoard::operator==(const OthelloBoard& ob) const {

	return ob.empty == empty && 
		ob.numOfPieces[WHITE] == numOfPieces[WHITE] &&
		ob.numOfPieces[BLACK] == numOfPieces[BLACK] &&
		ob.pieces[WHITE] == pieces[WHITE] &&
		ob.pieces[BLACK] == pieces[BLACK];
}

bool OthelloBoard::operator!=(const OthelloBoard& ob) const
{
	return !(*this == ob);
}

// currently Agent and OB both perform the same, slow cast for the same result on a move
// maybe cache the next wround of moves while the agent is searching?
void OthelloBoard::rollBack(Move move, Color player) {
	unflip(move.toFlip, move.numOfPieces, player);
	unplace(move.bi, player);
}

void OthelloBoard::unflip(bitboard toFlip, int flipCount, Color player) {
	pieces[player] &= ~toFlip;
	pieces[ci::opponent[player]] |= toFlip;

	numOfPieces[player] -= flipCount;
	numOfPieces[ci::opponent[player]] += flipCount;
}

void OthelloBoard::unplace(int pos, Color player) {
	pieces[player] &= ~(bbh::ONE << pos);
	empty |= bbh::ONE << pos;
	numOfPieces[player] -= 1;
}


int OthelloBoard::getNumOfPieces(Color player) {
	return numOfPieces[player];
}

int OthelloBoard::makeMove(Move move, Color player) {

	if (move.numOfPieces != 0) {
		flip(move.toFlip, move.numOfPieces, player);
		place(move.bi, player);
	}

	lastMove = move;
	return move.numOfPieces;
}

int OthelloBoard::makeMove(int bi, Color player) {
	Move move = getFlips(bi, player);
	return makeMove(move, player);
}

void OthelloBoard::place(int pos, Color c)
{
	pieces[c] |= bbh::ONE << pos;
	empty &= ~(bbh::ONE << pos);
	numOfPieces[c] += 1;

}


void OthelloBoard::flip(bitboard toFlip, int flipCount, Color player)
{
	pieces[player] |= toFlip;
	pieces[ci::opponent[player]] &= ~toFlip;

	numOfPieces[player] += flipCount;
	numOfPieces[ci::opponent[player]] -= flipCount;

}

//possible routes: lookup tables, bit-twiddling
Move OthelloBoard::getFlips(int bi, Color color) {

	Move result(bi,0,0,0);
	int x = bbh::BI_TO_XY[bi][0];
	int y = bbh::BI_TO_XY[bi][1];

	for (int dir = 0; dir < 8; dir++) {
		
		int xMod = bbh::DIRECTION_XY_MOD[dir][0];
		int yMod = bbh::DIRECTION_XY_MOD[dir][1];
		
		//lookup table candidate?
		//converts to x y to check if within bounds
		//slow
		bitboard cast = 0;
		bitboard lastCast = 0;
		
		for (int j = 1; 
			(x + j * xMod) <  8 && 
			(x + j * xMod) >= 0 && 
			(y + j * yMod) <  8 && 
			(y + j * yMod) >= 0
			; j++) {
			
			cast |= bbh::ONE << (bi + j * bbh::DIRECTION_BI_MOD[dir]);

			if (cast & empty) {
				break;
			}
			
			if (cast & pieces[color]) {
				result.numOfPieces += j - 1;
				result.toFlip |= lastCast;
				break;
			}

			lastCast = cast;
		}
	}
	return result;
}

void OthelloBoard::generateLegalMoves(Color player, Move(&moves)[64], int& size) {
	Color opponent = ci::opponent[player];

	std::uint64_t opponentEdges = getOpenEdges(opponent);

	size = 0;
	int nextOn;
	int pos = 64;

	while ((nextOn = __lzcnt64(opponentEdges) + 1) && (pos -= nextOn) >= 0) {
		
		Move result = getFlips(pos, player);
		if (result.numOfPieces != 0) {

			moves[size] = result;
			size += 1;
		}
		opponentEdges <<= nextOn;
	}

}

//TODO: MACRO?
bitboard OthelloBoard::getOpenEdges(Color color) {
	bitboard p = pieces[color];
	return OPEN_EDGES(p);
}
