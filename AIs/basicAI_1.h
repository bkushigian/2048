#ifndef _BASICAI_1
#define _BASICAI_1

#include "AI.h"
#include "../include/board_2048.h"

class basicAI_1 : AI {
public:
	basicAI_1();
	direction_t chooseMove(board_2048& board);
	
private:
	direction_t lastMove;
};

#endif
