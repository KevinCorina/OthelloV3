#include "AgentVersusAgentGame.h"
#include "CommandLinePlayer.h"
#include "CommandLineInterface.h"
#include "AlphaBetaAgent.h"

AgentVersusAgentGame::AgentVersusAgentGame() {
	init();
}

void AgentVersusAgentGame::init() {
	ob = new OthelloBoard();
	player1 = new AlphaBetaAgent(BLACK, ob);
	player2 = new AlphaBetaAgent(WHITE, ob);
}
