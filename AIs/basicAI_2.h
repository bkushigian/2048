#ifndef _ROWFILLAI_H
#define _ROWFILLAI_H

#include "AI.h"
#include "../include/board_2048.h"

class basicAI_2 : AI {
private:
	int moves = 0;
public:
	direction_t chooseMove(board_2048& board);
};

#endif
