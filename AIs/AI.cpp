#include "AI.h"
AI::AI(){
	
}
AI::~AI(){}
direction_t AI::chooseMove(board_2048& board) {
	direction_t result = NONE;
	if (board.isValidMove(UP) ) return (direction_t)-4;
	else if (board.isValidMove(LEFT)) return (direction_t)-1;
	else if (board.isValidMove(RIGHT)) return (direction_t)1;
	else if (board.isValidMove(DOWN)) return (direction_t)4;
	return (direction_t)0;
}
