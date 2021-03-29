#pragma once
#include <cstdint>
#include <string>

typedef std::uint64_t bitboard;

namespace bbh {
	
	namespace {
		constexpr char DEFAULT_HEADER[] = "\n  1 2 3 4 5 6 7 8\n +----------------";
		constexpr char A1_HEADER[] = "\n  a b c d e f g h\n +----------------";
	}

	constexpr int XY_TO_BI[8][8] = { { 0 ,8 ,16 ,24 ,32 ,40 ,48 ,56 }, {1, 9, 17, 25, 33, 41, 49, 57 }, {2, 10, 18, 26, 34, 42, 50, 58 }, {3, 11, 19, 27, 35, 43, 51, 59 }, {4, 12, 20, 28, 36, 44, 52, 60 }, {5, 13, 21, 29, 37, 45, 53, 61 }, {6, 14, 22, 30, 38, 46, 54, 62 }, {7, 15, 23, 31, 39, 47, 55, 63 } };
	constexpr int  BI_TO_XY[64][2] = { {0, 0},{1, 0},{2, 0},{3, 0},{4, 0},{5, 0},{6, 0},{7, 0},{0, 1},{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{0, 2},{1, 2},{2, 2},{3, 2},{4, 2},{5, 2},{6, 2},{7, 2},{0, 3},{1, 3},{2, 3},{3, 3},{4, 3},{5, 3},{6, 3},{7, 3},{0, 4},{1, 4},{2, 4},{3, 4},{4, 4},{5, 4},{6, 4},{7, 4},{0, 5},{1, 5},{2, 5},{3, 5},{4, 5},{5, 5},{6, 5},{7, 5},{0, 6},{1, 6},{2, 6},{3, 6},{4, 6},{5, 6},{6, 6},{7, 6},{0, 7},{1, 7},{2, 7},{3, 7},{4, 7},{5, 7},{6, 7},{7, 7} };
	
	// {UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT };
	constexpr int  DIRECTION_BI_MOD[8] = { -8,-7,1,9,8,7,-1,-9 };
	constexpr int  DIRECTION_XY_MOD[8][2] = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1} };

	constexpr bitboard FULL = 18446744073709551615;
	constexpr bitboard ONE = 1;
	constexpr bitboard NOT_RIGHT_EDGE = 18374403900871474942;
	constexpr bitboard NOT_LEFT_EDGE = 9187201950435737471;
	
	const char xToColumn(int x);
	const int columnToX(char col);

	const std::string bitBoardToString(bitboard* bbs, int size = 1, bool A1Origin = false, std::string symbols = "x");
	const bitboard bbFromBinaryString(std::string s);
	
	const std::string biToColRowString(int i);
}