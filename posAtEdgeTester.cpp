#include <iostream>
#include "include/board_2048.h"

using namespace std;
int main() {
	board_2048 b;
	b = board_2048();
	cout << "UP\n\t";
	for (int i = 0; i < 16; i++) {
		cout << b.posAtEdge(i, UP) << "  ";
		if ( i % 4 == 3 ) cout << endl << '\t';
	}
	cout << endl << endl << "DOWN\n\t";
	for (int i = 0; i < 16; i++) {
		cout << b.posAtEdge(i, DOWN) << "  ";
		if (i % 4 == 3) cout << endl << '\t';
	}
	cout << endl << endl << "RIGHT\n\t";
	for (int i = 0; i < 16; i++) {
		cout << b.posAtEdge(i, RIGHT) << "  ";
		if (i % 4 == 3) cout << endl << '\t';
	}
	cout << endl << endl << "LEFT\n\t";
	for (int i = 0; i < 16; i++) {
		cout << b.posAtEdge(i, LEFT) << "  ";
		if (i % 4 == 3) cout << endl << '\t';
	}
	
}
