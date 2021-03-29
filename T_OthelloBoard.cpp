#include "pch.h"

#include "BitboardHelper.h"
#include "OthelloBoard.h"

using namespace std;


TEST(OthelloBoard, Constructors) {
	OthelloBoard ob = OthelloBoard();

	ASSERT_EQ(ob.pieces[WHITE], bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00000000"
	));
	ASSERT_EQ(ob.pieces[BLACK], bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	ASSERT_EQ(ob.empty, bbh::bbFromBinaryString(
		"11111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111111"
	));

	OthelloBoard* obPoint = new OthelloBoard(
		"B...BBB."\
		".BBBBB.W"\
		"WWBBWWW."\
		".WBBBW.W"\
		".BWBWWB."\
		"...W.W.B"\
		".....W.."\
		".....W..");

	ob = OthelloBoard(*obPoint);

	ASSERT_EQ(ob.pieces[BLACK], obPoint->pieces[BLACK]);
	ASSERT_EQ(ob.pieces[WHITE], obPoint->pieces[WHITE]);
	ASSERT_EQ(ob.empty, obPoint->empty);
	ASSERT_EQ(ob.getNumOfPieces(WHITE), obPoint->getNumOfPieces(WHITE));
	ASSERT_EQ(ob.getNumOfPieces(BLACK), obPoint->getNumOfPieces(BLACK));
	ASSERT_EQ(ob.getNumOfPieces(BLACK), obPoint->getNumOfPieces(BLACK));

	ob.makeMove(bbh::XY_TO_BI[6][1], BLACK);
	ASSERT_NE(ob.pieces[BLACK], obPoint->pieces[BLACK]);

}


TEST(OthelloBoard, Place) {

	OthelloBoard ob = OthelloBoard();
	ob.place(bbh::XY_TO_BI[0][0], BLACK);
	ASSERT_EQ(ob.empty, bbh::bbFromBinaryString(
		"01111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111111"
	));


	ASSERT_EQ(ob.pieces[BLACK],  bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	ob.place(bbh::XY_TO_BI[7][7], BLACK);
	ASSERT_EQ(ob.empty, bbh::bbFromBinaryString(
		"01111111"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111110"
	));
	ASSERT_EQ(ob.pieces[BLACK] , bbh::bbFromBinaryString(
		"10000000"\
		"00000000"\
		"00000000"\
		"00001000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000001"
	));

	ob.place(bbh::XY_TO_BI[7][0], WHITE);
	ASSERT_EQ(ob.empty , bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"11111110"
	));
	ASSERT_EQ(ob.pieces[WHITE] , bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00000000"
	));

	ob.place(bbh::XY_TO_BI[0][7], WHITE);
	ASSERT_EQ(ob.empty , bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111111"\
		"01111110"
	));
	ASSERT_EQ(ob.pieces[WHITE] , bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"10000000"
	));

	ob.place(bbh::XY_TO_BI[6][6], WHITE);
	ASSERT_EQ(ob.empty , bbh::bbFromBinaryString(
		"01111110"\
		"11111111"\
		"11111111"\
		"11100111"\
		"11100111"\
		"11111111"\
		"11111101"\
		"01111110"
	));
	ASSERT_EQ(ob.pieces[WHITE] , bbh::bbFromBinaryString(
		"00000001"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00001000"\
		"00000000"\
		"00000010"\
		"10000000"
	));


}
TEST(OthelloBoard, Flip) {
	OthelloBoard ob = OthelloBoard(
		bbh::bbFromBinaryString(
			"00000000"\
			"00001000"\
			"00001000"\
			"00001100"\
			"00001000"\
			"00100100"\
			"00110010"\
			"00000000"
		),
		bbh::bbFromBinaryString(
			"00000000"\
			"00000000"\
			"00000000"\
			"00000010"\
			"00000000"\
			"00000000"\
			"00000000"\
			"00000001"
		)
	);

	ob.flip(bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001100"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000000")
		, 7, WHITE);

	ASSERT_EQ(ob.pieces[WHITE], bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00001110"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000001")
	);
	ASSERT_EQ(ob.pieces[BLACK] , bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00100000"\
		"00110000"\
		"00000000"
	));

	
}

TEST(OthelloBoard, RollBack) {
	OthelloBoard ob = OthelloBoard(
		bbh::bbFromBinaryString(
			"00000000"\
			"00001000"\
			"00001000"\
			"00001100"\
			"00001000"\
			"00100100"\
			"00110010"\
			"00000000"
		),
		bbh::bbFromBinaryString(
			"00000000"\
			"00000000"\
			"00000000"\
			"00000010"\
			"00000000"\
			"00000000"\
			"00000000"\
			"00000001"
		)
	);
	
	Move moves[64];
	int size;
	ob.generateLegalMoves(WHITE, moves, size);

	OthelloBoard obFirst(ob);

	ob.makeMove(moves[0], WHITE);
	ASSERT_NE(obFirst, ob);

	ob.rollBack(moves[0], WHITE);

	ASSERT_EQ(obFirst, ob);
}
TEST(OthelloBoard, Move) {
	OthelloBoard ob = OthelloBoard(
		bbh::bbFromBinaryString(
			"00000000"\
			"00001000"\
			"00001000"\
			"00001100"\
			"00001000"\
			"00100100"\
			"00110010"\
			"00000000"
		),
		bbh::bbFromBinaryString(
			"00000000"\
			"00000000"\
			"00000000"\
			"00000010"\
			"00000000"\
			"00000000"\
			"00000000"\
			"00000001"
		)
	);

	ASSERT_EQ(ob.makeMove(bbh::XY_TO_BI[3][3], WHITE), 5);

	ASSERT_EQ(ob.empty, bbh::bbFromBinaryString(
		"11111111"\
		"11110111"\
		"11110111"\
		"11100001"\
		"11110111"\
		"11011011"\
		"11001101"\
		"11111110"
	));

	ASSERT_EQ(ob.pieces[WHITE] , bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00011110"\
		"00001000"\
		"00000100"\
		"00000010"\
		"00000001")
	);
	ASSERT_EQ(ob.pieces[BLACK] , bbh::bbFromBinaryString(
		"00000000"\
		"00001000"\
		"00001000"\
		"00000000"\
		"00000000"\
		"00100000"\
		"00110000"\
		"00000000"
	));



	

}
TEST (OthelloBoard, EdgeGeneration) {
	
	OthelloBoard ob = OthelloBoard(bbh::bbFromBinaryString(
		"00000000"\
		"00100000"\
		"00010000"\
		"00000000"\
		"00110000"\
		"01000000"\
		"00000000"\
		"00000000"
	), bbh::bbFromBinaryString(
		"00000000"\
		"00010000"\
		"00000000"\
		"00011100"\
		"00001100"\
		"00000100"\
		"00000000"\
		"00000000"
	));
	ASSERT_EQ(ob.getOpenEdges(WHITE) , bbh::bbFromBinaryString(
		"00111000"\
		"00001000"\
		"00101110"\
		"00100010"\
		"00000010"\
		"00011010"\
		"00001110"\
		"00000000"));


	ob = OthelloBoard(bbh::bbFromBinaryString(
		"10000001"\
		"00011000"\
		"00100000"\
		"10000000"\
		"10010000"\
		"00100000"\
		"01000000"\
		"10000001"
	), bbh::bbFromBinaryString(
		"01000000"\
		"00100000"\
		"00000000"\
		"00011100"\
		"00000000"\
		"00000000"\
		"10000010"\
		"00000000"
	));
	std::uint64_t edgesActual = ob.getOpenEdges(BLACK);
	std::uint64_t edgesExpected = bbh::bbFromBinaryString(
		"00111110"\
		"11000111"\
		"11011100"\
		"01100000"\
		"01101000"\
		"11011000"\
		"00110001"\
		"01100010");

	ASSERT_EQ(ob.getOpenEdges(BLACK) , bbh::bbFromBinaryString(
		"00111110"\
		"11000111"\
		"11011100"\
		"01100000"\
		"01101000"\
		"11011000"\
		"00110001"\
		"01100010"));

}



void compareMoveResults(Move actualMoves[], int actualSize, Move expectedMoves[], int expectedSize) {

	ASSERT_EQ(actualSize, expectedSize);

	for (int i = 0; i < expectedSize; i++) {
		Move a = actualMoves[i];
		Move e = expectedMoves[i];

		ASSERT_EQ(a.bi, e.bi);
		ASSERT_EQ(a.numOfPieces, e.numOfPieces);
	}
}



TEST(OthelloBoard, MoveGeneration) {

	OthelloBoard ob = OthelloBoard();

	Move moves[64];
	int size;

	ob.generateLegalMoves(BLACK, moves, size);


	Move expected1[] = {
		Move(bbh::XY_TO_BI[4][5], 1),
		Move(bbh::XY_TO_BI[5][4], 1),
		Move(bbh::XY_TO_BI[2][3], 1),
		Move(bbh::XY_TO_BI[3][2], 1),
	};

	compareMoveResults(moves, size, expected1, 4);

	ob = OthelloBoard(
		"........"\
		"..BW...."\
		"...B...."\
		"...WWW.."\
		"..BBWW.."\
		".B...W.."\
		"........"\
		"........");

	Move expected2[6] = {
		Move(bbh::XY_TO_BI[6][5], 2),
		Move(bbh::XY_TO_BI[6][4], 2),
		Move(bbh::XY_TO_BI[5][2], 1),
		Move(bbh::XY_TO_BI[4][2], 1),
		Move(bbh::XY_TO_BI[4][1], 1),
		Move(bbh::XY_TO_BI[3][0], 1),
	};


	ob.generateLegalMoves(BLACK, moves, size);

	compareMoveResults(moves, size, expected2, 6);
	ob = OthelloBoard(
		"........"\
		"...B...."\
		"..B.B..."\
		".BBBWB.."\
		".BBBBW.."\
		".....BWB"\
		"......WW"\
		"......WB");

	Move expected3[10] = {
		Move(bbh::XY_TO_BI[5][6], 1),
		Move(bbh::XY_TO_BI[4][5], 2),
		Move(bbh::XY_TO_BI[2][5], 1),
		Move(bbh::XY_TO_BI[7][4], 1),
		Move(bbh::XY_TO_BI[0][4], 4),
		Move(bbh::XY_TO_BI[6][3], 1),
		Move(bbh::XY_TO_BI[0][3], 3),
		Move(bbh::XY_TO_BI[5][2], 1),
		Move(bbh::XY_TO_BI[4][1], 1),
		Move(bbh::XY_TO_BI[1][1], 4),
	};

	ob.generateLegalMoves(WHITE, moves, size);


	compareMoveResults(moves, size, expected3, 10);
	ob = OthelloBoard(
		"..B.W..."\
		"...W.B.."\
		"WBW.B..."\
		"WWBBBW.B"\
		"WWWBBWB."\
		".WW.BBBW"\
		"BWW.B.WB"\
		"....BWWW");

	Move expected4[13] = {

		Move(bbh::XY_TO_BI[2][7], 3),
		Move(bbh::XY_TO_BI[1][7], 4),
		Move(bbh::XY_TO_BI[0][7], 2),
		Move(bbh::XY_TO_BI[5][6], 1),
		Move(bbh::XY_TO_BI[3][6], 2),
		Move(bbh::XY_TO_BI[0][5], 1),
		Move(bbh::XY_TO_BI[7][4], 1),
		Move(bbh::XY_TO_BI[6][3], 2),
		Move(bbh::XY_TO_BI[6][2], 1),
		Move(bbh::XY_TO_BI[5][2], 2),
		Move(bbh::XY_TO_BI[3][2], 1),
		Move(bbh::XY_TO_BI[2][1], 1),
		Move(bbh::XY_TO_BI[1][1], 1),
	};


	ob.generateLegalMoves(BLACK, moves, size);
	compareMoveResults(moves, size, expected4, 13);

}
TEST(OthelloBoard, FlipGeneration) {
	OthelloBoard ob = OthelloBoard();
	auto m = ob.getFlips(bbh::XY_TO_BI[2][3], BLACK);
	ASSERT_EQ(m.numOfPieces, 1);
	ASSERT_EQ(m.toFlip, bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00000000"\
		"00010000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"));



	ob = OthelloBoard(bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"01100000"\
		"00111001"\
		"00000000"\
		"00010000"\
		"00000000"\
		"00000000"
	), bbh::bbFromBinaryString(
		"01000000"\
		"00010000"\
		"00000000"\
		"00000100"\
		"01000100"\
		"00000000"\
		"00000000"\
		"00000000"
	));
	m = ob.getFlips(bbh::XY_TO_BI[1][3], WHITE);
	ASSERT_EQ(m.numOfPieces , 4);
	ASSERT_EQ(m.toFlip , bbh::bbFromBinaryString(
		"00000000"\
		"00000000"\
		"00100000"\
		"00111000"\
		"00000000"\
		"00000000"\
		"00000000"\
		"00000000"));



}