#include "rowFill.hpp"

direction_t rowfillAI::chooseMove(board_2048& board) {
	if (! board.hasMove()) return NONE;
	++moves;
	if (moves > autoMoves && board.getPosOfEmpty().size() < 12)
		return predChooseMove(board, EVAL_DEPTH);

	if (board.isValidMove(LEFT)) 		return LEFT;
	if (board.isValidMove(UP)) 		return UP;
	if (board.isValidMove(RIGHT))		return RIGHT;
	if (board.isValidMove(DOWN))		return DOWN;
	return NONE;

}
