#include "pch.h"
#include "BitboardHelper.h"
#include <intrin.h>
#include <CommandLineInterface.h>
using namespace std;

TEST(BitboardHelper, BitboardToIndices ) {

	std::uint64_t bb = bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00001100"\
		"00001000"\
		"00100100"\
		"00110010"\
		"00000000"
	);

	int expected[10][2] = { {6,6},{3,6},{2,6},{5,5},{2,5},{4,4},{5,3},{4,3},{4,2},{4,1} };

	int i = 0;
	int nextOn = 0;
	int pos = 64;

	while ((nextOn = __lzcnt64(bb) + 1) ^ 64 && !bb) {
		pos -= nextOn;
		cli::comment("expected\t" + std::to_string(expected[i][0]) + ",\t" + std::to_string(expected[i][1]));
		cli::comment("actual\t" + std::to_string(bbh::BI_TO_XY[pos][0]) + ",\t" + std::to_string(bbh::BI_TO_XY[pos][1]));


		ASSERT_TRUE(bbh::BI_TO_XY[pos][0] == expected[i][0]);
		ASSERT_TRUE(bbh::BI_TO_XY[pos][1] == expected[i][1]);

		bb <<= nextOn;
		i++;
	}

	
	bb = bbh::bbFromBinaryString(
		"11111111"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"11111111"
	);


	int expected1[16][2] = { {7,7},{6,7},{5,7},{4,7},{3,7},{2,7},{1,7},{0,7},{7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0},{0,0} };

	i = 0;
	nextOn = 0;
	pos = 64;

	while ((nextOn = __lzcnt64(bb) + 1) ^ 64 && !bb) {

		pos -= nextOn;

		ASSERT_EQ(bbh::BI_TO_XY[pos][0], expected1[i][0]);
		ASSERT_EQ(bbh::BI_TO_XY[pos][1], expected1[i][1]);

		bb <<= nextOn;
		i++;
	}



	bb = bbh::bbFromBinaryString(
		"00010100"\
		"11101000"\
		"00010110"\
		"00000010"\
		"00000001"\
		"10010000"\
		"00010100"\
		"11110000"
	);


	int expected2[19][2] = { {3,7},{2,7},{1,7},{0,7},{5,6},{3,6},{3,5},{0,5},{7,4},{6,3},{6,2},{5,2},{3,2},{4,1},{2,1},{1,1},{0,1}, {5,0}, {3,0} };

	i = 0;
	nextOn = 0;
	pos = 64;

	while ((nextOn = __lzcnt64(bb) + 1) ^ 64 && !bb) {

		pos -= nextOn;


		ASSERT_EQ(bbh::BI_TO_XY[pos][0], expected2[i][0]);
		ASSERT_EQ(bbh::BI_TO_XY[pos][1], expected2[i][1]);

		bb <<= nextOn;
		i++;
	}


	bb = bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"\
	);


	int expected3[1][2] = { {0,0} };

	i = 0;
	nextOn = 0;
	pos = 64;

	while ((nextOn = __lzcnt64(bb) + 1) ^ 64 && !bb) {

		pos -= nextOn;


		ASSERT_EQ(bbh::BI_TO_XY[pos][0], expected3[i][0]);
		ASSERT_EQ(bbh::BI_TO_XY[pos][1], expected3[i][1]);

		bb <<= nextOn;

		i++;
	}

	
}