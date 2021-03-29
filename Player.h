#pragma once
#include "Color.h"
#include "Move.h"

class Player {
public:
	Color color;
	bool passedLastTurn = false;
	Player(Color color) {
		this->color = color;
	}

	virtual void notify(Move move) = 0;
	virtual Move nextMove() = 0;
	
};