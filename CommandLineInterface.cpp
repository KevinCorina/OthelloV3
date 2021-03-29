#include "Color.h"

#include "CommandLineInterface.h"
#include "BitboardHelper.h"
#include <sstream> 
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include "Move.h"
#include <fstream>
#include "OthelloGame.h"





const std::string cli::nextNonComment() {
	std::string input;
	do {
		std::getline(std::cin, input);
	} while (input.at(0) == 'C');
	return input;
}

const void cli::comment(std::string toComment) {

	std::istringstream stream(toComment);
	std::string line;
	while (std::getline(stream, line)) {
		printf("C %s\n", line.c_str());
	}


}


const Color cli::getInitalizerColor() {
	comment("Enter the agent color ('I B' or 'I W'):");
	std::string input = nextNonComment();
	return (input.at(2) == ci::colorChar[BLACK] ? BLACK : WHITE);
}

const void cli::signalReady(Color color) {
	printf("R %c\n", ci::colorChar[color]);
}

const void cli::printAgentMove(Move move, Color color) {
	if (move.bi == OthelloGame::PASS_BI_FLAG) {
		printf("%c\n", ci::colorChar[color]);

	}	else {
		auto xy = bbh::BI_TO_XY[move.bi];
		//Referee interface indices are base a,1; in-game board rep is base 0,0.
		printf("%c %c %u\n", ci::colorChar[color], bbh::xToColumn(xy[0]), xy[1] + 1);
	}
}

const void cli::signalEndGame(int numOfBlackPieces) {
	//printf("%u\n", numOfBlackPieces);
}

const int cli::nextOpponentMoveBI()
{
	comment("Enter your color and move ('B c r' or 'W c r', where c is a lowercase letter 'a'-'h' and r is an integer 1-8):");
	std::string input = nextNonComment();
	if (input.length() == 1) {
		//return OthelloGame::PASS;
		return -1;
	}
	else {
		return (bbh::XY_TO_BI[bbh::columnToX(input.at(2))][input.at(4) - '0' - 1]);
	}

}