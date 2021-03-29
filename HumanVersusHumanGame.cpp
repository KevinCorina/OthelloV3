#include "HumanVersusHumanGame.h"
#include "CommandLinePlayer.h"

HumanVersusHumanGame::HumanVersusHumanGame() {
	init();
}


void HumanVersusHumanGame::init() {
	ob = new OthelloBoard();
	player1 = new CommandLinePlayer(BLACK, ob);
	player2 = new CommandLinePlayer(WHITE, ob);
}
