#include "board.hpp"

ullong_t	TILE_FLAG 		= 15;		// First 5 bits set to 1, all others set to 0;
int		TILE_WIDTH		= 4;		// Number of bits in a tile
int		BOARD_SIZE		= 16;		// Number of tiles in board

tile_t  board::operator[] (pos_t p) const {
	tile_t result =(b >> p) & TILE_FLAG;
	return result;
}

void  board::set(pos_t p, ullong_t v){
	b &= !(TILE_FLAG << p);
	b |= (v << p);
}

bool board::up(){
	bool madeMove = false;
	pos_t pos;
	ushort_t merged = 0;
	for (short i = 4; i < 16; i += 4) {
		for (short j = 0; j < 4; ++j) {
			if ( (*this)[i + j] == 0 ) break;
			pos = i + j + UP;
			while ( (merged | (1 << pos)) && pos > 3 && (*this)[pos] == 0 ){
				pos += UP;
			}
			if ( merged | (1 << pos) ) break;			// This cell has already
			if ( (*this)[i + j] == (*this)[pos] ) {
				set(pos, (*this)[pos] + 1);
				set(i + j,  0);
				merged |= (1 << pos);
				madeMove = true;
			}
			else if ( i + j != pos - UP ) {
				set(pos + DOWN, (*this)[i + j]);
				set(i + j,  1);
				madeMove = true;
			}
		}
	}
}
bool board::move(dir_t d) {
	switch (d) {
		case UP: return up();
		default: return false;
	}
}

ullong_t board::getBoard() {
	return (*this).b;
}

void drawBoard(board b) {
	for (ubyte_t i = 0; i < 15; ++i){
		std::cout << (1 << b[i]) << "   ";
		if (i % 4 == 3) std::cout << std::endl;
	}
	std::cout << std::endl;
}

void drawBoardBin(board b) {
	ullong_t brd = b.getBoard();
	for (int nib = 1; nib < 17; ++ nib){
		for (short pos = 3; pos >= 0; -- pos) {
			std::cout << (( brd >> (4 * nib - pos))&1);
		}
		if (nib % 4 == 0) std::cout << std::endl;
		else std::cout << ' ';

	}
	std::cout << std::endl;
}
