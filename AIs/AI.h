#ifndef _AI
#define _AI

#include "../include/board_2048.h"

class AI {
public:
	AI();
	~AI();
	direction_t chooseMove(board_2048& board);
};

#endif
