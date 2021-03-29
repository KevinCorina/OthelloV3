#pragma once

#include "Player.h"
#include "OthelloBoard.h"

class CommandLinePlayer : public Player {
private:
	OthelloBoard* ob;
public:
	CommandLinePlayer(Color color, OthelloBoard* ob);

	void notify(Move makeMove);
	Move nextMove();
};