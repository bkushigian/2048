#include "rowFill.hpp"

direction_t rowfillAI::chooseMove(board_2048& board) {
	moves++;
	if (board.numberOfMerges(UP) > board.numberOfMerges(RIGHT)) {
		return UP;
	}
	else if (board.numberOfMerges(UP) < board.numberOfMerges(RIGHT)) {
		return RIGHT;
	}
	//else if (board.numberOfMerges(UP) == 0) { // this also implies numberofmerges(RIGHT) = 0
	if (board.isValidMove(UP)) return UP;
	else if (board.isValidMove(RIGHT)) return RIGHT;
	else if (board.isValidMove(LEFT)) return LEFT;
	else if (board.isValidMove(DOWN))return DOWN;
	return NONE;
}
