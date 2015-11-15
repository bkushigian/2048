#ifndef _ROWFILLAI_H
#define _ROWFILLAI_H

#include "AI.hpp"
#include "../include/board_2048.hpp"

class rowfillAI : AI {
private:
	int moves;
public:
	rowfillAI(){moves = 0;}
	direction_t chooseMove(board_2048& board);
};

#endif
