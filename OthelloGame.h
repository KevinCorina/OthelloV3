#pragma once
#include "Player.h"
#include "OthelloBoard.h"

class OthelloGame {
protected:
	virtual void init() = 0;
	Player* player1;
	Player* player2;
	OthelloBoard* ob;
	bool running;
public:
	~OthelloGame();
	static const int PASS_BI_FLAG = -1;
	Player* opponent(Player* p);
	void start();
	void endGame();

};