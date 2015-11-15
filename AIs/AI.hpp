#ifndef _AI
#define _AI

#include "../include/board_2048.hpp"

class AI {
public:
	AI();
	~AI();
	direction_t chooseMove(board_2048& board);
};

#endif
