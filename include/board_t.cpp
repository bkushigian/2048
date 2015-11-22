#include "board_t.hpp"
board_t::board_t(){
	for (int i = 0; i < 16; ++i) values[i] = 0;
}
board_t::board_t(unsigned int b[16]) {
	for (int i = 0; i < 16; i++) {
		values[i] = b[i];
	}
}
board_t::board_t(board_t const& other) {
	for (int i = 0; i < 16; ++i) this->values[i] = other.values[i];
}
