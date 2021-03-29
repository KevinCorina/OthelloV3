#pragma once

#include <string>
#include "Color.h"
#include "Move.h"

namespace cli {

	const bool DEBUG = true;

	const std::string nextNonComment();
	const void comment(std::string toComment);
	const Color getInitalizerColor();
	const void signalReady(Color color);
	const void printAgentMove(Move move, Color color);
	const void signalEndGame(int numOfBlackPieces);
	const int nextOpponentMoveBI();

};