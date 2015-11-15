#ifndef _BASICAI_1
#define _BASICAI_1

#include "AI.hpp"
#include "../include/board_2048.hpp"

class basicAI_1 : AI {
public:
	basicAI_1();
	direction_t chooseMove(board_2048& board);

private:
	direction_t lastMove;
};

#endif
