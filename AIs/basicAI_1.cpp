#include "basicAI_1.hpp"

basicAI_1::basicAI_1(){
	lastMove = NONE;
}
direction_t basicAI_1::chooseMove(board_2048& board){
	if (lastMove == NONE) {
		if (board.isValidMove(UP)) {lastMove = UP;return UP;}
		lastMove = LEFT;
		return LEFT;

	}
	if (lastMove == UP || lastMove == DOWN) {
		if (board.isValidMove(LEFT)) {
			lastMove = LEFT;
			return LEFT;
		}
		if (board.isValidMove(RIGHT)){
			lastMove = RIGHT;
			return RIGHT;
		}
		if (board.isValidMove(UP)) {
			lastMove = UP;
			return UP;
		}
		lastMove = DOWN;
		return DOWN;
	}

	if (lastMove == LEFT){
		if (board.isValidMove(RIGHT)){
			lastMove = RIGHT;
			return RIGHT;
		}
		if (board.isValidMove(UP)) {
			lastMove = UP;
			return UP;
		}
		if (board.isValidMove(LEFT)) {
			lastMove = LEFT;
			return LEFT;
		}
		lastMove = DOWN;
		return DOWN;
	}

	if (lastMove == RIGHT){

		if (board.isValidMove(UP)) {
			lastMove = UP;
			return UP;
		}
		if (board.isValidMove(LEFT)) {
			lastMove = LEFT;
			return LEFT;
		}
		if (board.isValidMove(RIGHT)){
			lastMove = RIGHT;
			return RIGHT;
		}
		lastMove = DOWN;
		return DOWN;
	}

}
