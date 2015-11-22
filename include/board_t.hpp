#ifndef BOARD_T_H
#define BOARD_T_H
#include <iostream>
struct board_t {
	board_t();
	board_t(unsigned int b[16]);
	board_t(board_t const& other);
	unsigned int values[16];
};

#endif
