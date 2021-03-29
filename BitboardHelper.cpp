#include "BitboardHelper.h"
#include <string>
#include <algorithm>

//ASCII alphabet starts at 48
const char bbh::xToColumn(int x) {
	return (char)('a' + x);
}
const int bbh::columnToX(char col) {
	return (int)(col - 'a');
}


const std::string bbh::bitBoardToString(bitboard* bbs, int size, bool A1Origin, std::string symbols)
{
	
	std::string out = DEFAULT_HEADER;

	if (A1Origin) {
		out = A1_HEADER;
	}

	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) {
			out.append("\n" + std::to_string(A1Origin + i / 8) + "|");
		}
		std::uint64_t pos = ONE << i;
		std::string atPos = " ";

		for (int j = 0; j < size; j++) {
			if (bbs[j] & pos) {
				atPos = symbols[j];
				break;
			}
		}
		out.append(atPos + " ");

	}
	return out;
	return "";
}

const bitboard bbh::bbFromBinaryString(std::string s)
{
	std::reverse(s.begin(), s.end());
	const char* s2 = s.c_str();
	uint64_t val = std::strtoull(s2, NULL, 2);
	return val;
}


const std::string bbh::biToColRowString(int i)
{
	return "(" + std::string(1, xToColumn(BI_TO_XY[i][0])) + ", " + std::to_string(BI_TO_XY[i][1] + 1) + ")";
}
