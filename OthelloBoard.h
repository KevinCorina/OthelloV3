#pragma once
#include <string>
#include "Color.h"
#include "Move.h"


class OthelloBoard {
private:
	int numOfPieces[2] = { 0,0 };
	Move lastMove;
public:

	void rollBack(Move move, Color player);
	void unplace(int pos, Color player);
	void unflip(bitboard, int flipCount, Color player);

	int getNumOfPieces(Color player);
	
	bitboard pieces[2] = { 0,0 };
	bitboard empty = 18446744073709551615;

	int makeMove(Move move, Color player);
	int makeMove(int pos, Color player);

	void place(int pos, Color c);
	void flip(bitboard, int flipCount, Color player);

	Move getFlips(int toPlace, Color player);

	void generateLegalMoves(Color player, Move (&moves)[64], int& size);
	bitboard getOpenEdges(Color color);

	OthelloBoard();
	OthelloBoard(std::string richString);
	OthelloBoard(const OthelloBoard& ob);
	OthelloBoard(bitboard black, bitboard white);

	std::string toString(bool A1Origin = false);

	//For use with gtest
	bool operator== (const OthelloBoard& ob) const;
	bool operator!= (const OthelloBoard& ob) const;

};