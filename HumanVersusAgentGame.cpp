#include "HumanVersusAgentGame.h"
#include "CommandLinePlayer.h"
#include "CommandLineInterface.h"
#include "AlphaBetaAgent.h"

HumanVersusAgentGame::HumanVersusAgentGame() {
	init();
}

void HumanVersusAgentGame::init() {
	ob = new OthelloBoard();
	Color agentColor = cli::getInitalizerColor();
	player1 = new AlphaBetaAgent(agentColor, ob);
	player2 = new CommandLinePlayer(ci::opponent[agentColor], ob);
	cli::signalReady(agentColor);

}
