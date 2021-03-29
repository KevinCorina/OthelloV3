#include "CommandLinePlayer.h"
#include "CommandLineInterface.h"
#include "Color.h"
#include "OthelloBoard.h"

CommandLinePlayer::CommandLinePlayer(Color color, OthelloBoard* ob): Player(color), ob(ob) {}


void CommandLinePlayer::notify(Move move) {
	cli::printAgentMove(move, ci::opponent[color]);
}

Move CommandLinePlayer::nextMove() {
	return ob->getFlips(cli::nextOpponentMoveBI(), color);
}
