#include "AlphaBetaAgent.h"
#include "OthelloBoard.h"
#include "BitboardHelper.h"
#include "CommandLineInterface.h"
#include "OthelloGame.h"
#include <float.h>

using namespace std;

AlphaBetaAgent::AlphaBetaAgent(Color color, OthelloBoard* ob) : Player(color), ob(ob) {}

double AlphaBetaAgent::evaluateBoard(OthelloBoard* toEvaluate) {
	return (double(toEvaluate->getNumOfPieces(color)) - double(toEvaluate->getNumOfPieces(ci::opponent[color])))/ (double(toEvaluate->getNumOfPieces(color)) + double(toEvaluate->getNumOfPieces(ci::opponent[color])));
}
Move AlphaBetaAgent::alphaBetaSearch(OthelloBoard currentBoard, Move lastMove, Color player, double alpha, double beta, int depth, bool maximizing) {
	if (depth == maxDepth || currentBoard.empty == 0 || time(NULL) >= searchLimit) {
		lastMove.score = evaluateBoard(&currentBoard);
		return lastMove;
	} else {
		Move moves[64];
		int size;
		currentBoard.generateLegalMoves(player, moves, size);
		
		if (size == 0) {
			moves[0] = Move(OthelloGame::PASS_BI_FLAG, 0, 0, DBL_MIN);
			size = 1;
		}
		
		int bestMoveIndex = 0;

		for (int i = 0; i < size; i++) {
			currentBoard.makeMove(moves[i], player);
			moves[i].score = alphaBetaSearch(currentBoard, moves[i], ci::opponent[player], alpha, beta, depth + 1, !maximizing).score;
			currentBoard.rollBack(moves[i], player);

			if (maximizing) {
				if (moves[bestMoveIndex].score < moves[i].score)
					bestMoveIndex = i;
				if (moves[bestMoveIndex].score >= beta)
					break;
				alpha = std::max(alpha, moves[bestMoveIndex].score);
			} else {
				if (moves[bestMoveIndex].score > moves[i].score) {
					bestMoveIndex = i;
				}
				if (moves[bestMoveIndex].score <= alpha)
					break;
				beta = std::min(beta, moves[bestMoveIndex].score);
			}

		}
		return moves[bestMoveIndex];
	}
}

Move AlphaBetaAgent::alphaBetaSearch() {
	
	searchLimit = time(NULL) + searchDuration[moveNum];

	moveNum++;

	OthelloBoard toSearch(*ob);
	Move move = alphaBetaSearch(toSearch, Move(), color, DBL_MIN, DBL_MAX, 0, true);

	return move;
}


//ideas:
//-maybe use notify() to track the amount of time the opponent takes
//-...or extracty "notify" out of Player and into a "listener" class so only CLP needs to implement it
//-frontier strategy - consider potential mobility and stability of disk
//-""stoner move"" corner stealing
//-lookup tables - generate at a compile time, search early moves
//-use multithreading to batch searches AND search while opponent is "thinking" (effectively doubling search time)


void AlphaBetaAgent::notify(Move makeMove)
{
}

Move AlphaBetaAgent::nextMove() {
	return alphaBetaSearch();
}

void AlphaBetaAgent::setDepth(int maxDepth) {
	this->maxDepth = maxDepth;
}

void AlphaBetaAgent::setMoveNum(int move) {
	this->moveNum = move;
}
