#include <iostream>
#include "include/board_2048.h"
#include "include/array_t.h"
#include <string>

using namespace std;

string evalFunctionString = "\t0) break \n\
	\t1) boardIsFull() \n \
	\t2) hasMove() \n\
	\t3) inCorner(int val) \n\
	\t4) getHighestVal() \n\
	\t5) numberOfMerges(direction_t dir)\n\
	\t6) columnOrder(int col) \n\
	\t7) rowOrder(int row) \n";

void drawBoard(board_2048& b){

	for (int i = 0; i < 16; i++) {
		cout.width(7);
		cout << b.getVal(i);
		cout.width(1);
		cout << " | ";
		if (i % 4 == 3)
			cout << '\n';
	}

}

void executeEvalFunction(board_2048& b){
	// Lists all eval functions, executes selected
	bool repeat = true;
	int selection;
	while (repeat){ 
		cout << evalFunctionString << endl;
		cin >> selection;
		if (0 > selection || selection > 7) {
			cout << "Bad Selection";
		}
		else if (selection == 0) break;
		else {
			switch (selection) {
				
				case 0:
					repeat = false;
					break;
				case 1:
					cout << "boardIsFull(): " << b.boardIsFull() << endl;
					break;
				case 2:
					cout << "hasMove(): " << b.hasMove() << endl;
					break;
				case 3:
					cout << "inCorner(int val): Enter value: ";
					int val;
					cin >> val;
					cout << "inCorner(" << val << "): Not implemented\n";
					break;
				case 4:
					cout << "getHighestVal(): " << b.getHighestVal() << endl;
					break;
				case 5:
					cout << "numberOfMerges(UP) = " <<  b.numberOfMerges(UP) << endl;
					cout << "numberOfMerges(DOWN) = " << b.numberOfMerges(DOWN) << endl;
					cout << "numberOfMerges(LEFT) = " << b.numberOfMerges(LEFT) << endl;
					cout << "numberOfMerges(RIGHT) = " << b.numberOfMerges(RIGHT) << endl;
					break;
				case 6:
					for (int col = 0; col < 4; col++) 
						cout << "columnOrder(" << col << "): " << (int)b.columnOrder(col) << endl;
					break;
				case 7:
					for (int row = 0; row < 4; row++) 
						cout << "rowOrder(" << row << "): " << (int)b.rowOrder(row) << endl;
					break;
			}
		}
		char c;
		cin >> c;
	}
}

int main(int argc, const char* argv[]) {
	int b[16] = {16,16,2,2,
				2,2,2,2,
				4,4,4,4,
				2,2,2,2};
	board_2048 board = board_2048(b);
	board.init();
	char ch = 'd';
	while (1) {
		drawBoard(board);		
		cout << "Enter (U)p, (D)own, (L)eft, (R)ight: ";	
		cin >> ch;
		switch (ch) {
			case 'd':
			case 'D':
				board.move(DOWN);
				break;
			case 'u':
			case 'U':
				board.move(UP);
				break;
			case 'r':
			case 'R':
				board.move(RIGHT);
				break;
			case 'l':
			case 'L':
				board.move(LEFT);
				break;
			case 'e':
			case 'E':
				executeEvalFunction(board);
				break;
			case 'x':
			case 'X':
			case 'q':
			case 'Q':
				return 0;
		}
		
	}
}
