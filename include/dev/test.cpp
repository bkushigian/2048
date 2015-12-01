#include "board.hpp"

int main() {
	int x = 0b1;

	board b;
	//b.set(2, 1);
	drawBoard(b);
	drawBoardBin(b);
	b.up();
	drawBoard(b);
	std::cout << std::endl << std::endl;
	drawBoardBin(b);
	std::cout << x;
}
