#ifndef _ROWFILLAI_H
#define _ROWFILLAI_H

#include "AI.hpp"
#include "../include/board_2048.hpp"

class basicAI_2 : AI {
private:
	int moves;
public:
	basicAI_2(){moves = 0;}
	direction_t chooseMove(board_2048& board);
};

#endif
