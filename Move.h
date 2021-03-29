#pragma once
#include "BitboardHelper.h"

struct Move {
	
	int bi = 0;
	int numOfPieces = 0;
	std::uint64_t toFlip = 0;
	
	double score = 0;

	Move();
	Move(int bi, int numOfPieces, bitboard toFlip = 0, double score = 0);
};

