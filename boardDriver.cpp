#include <iostream>
#include "include/board_2048.h"
#include "include/array_t.h"
#include <ncurses.h>
#include <sstream>
#include <unistd.h>
#include <math.h>
#include "AIs/AI.h"
#include "AIs/basicAI_1.h"
#include "AIs/rowFill.h"

using namespace std;

int y_0 = 6, x_0 = 10;
int squareWidth = 9;
int squareHeight = 4;
int WIDTH = 4 * squareWidth + 2 * x_0;
int HEIGHT = 4 * squareHeight + 2 * y_0;
int score_y = 2, score_x = WIDTH/2;

int highScore = 0;
int numberOfGames = 100;

int gameNumber = 0;

unsigned int SLEEP_TIME = 100000;

char* EMPTY_STRING;
stringstream ss;			// Store Numbers

bool usingAI = true;

AI myAI;
basicAI_1 basicAI;
rowfillAI rowfillAI;



void drawSquare(int pos, board_2048& b) {
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_RED);
	init_pair(3, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(4, COLOR_BLUE, COLOR_YELLOW);
	init_pair(5, COLOR_YELLOW, COLOR_BLUE);
	init_pair(6, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(7, COLOR_RED, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(10, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(11, COLOR_BLUE, COLOR_GREEN);
	init_pair(12, COLOR_GREEN, COLOR_RED);
	init_pair(13, COLOR_RED, COLOR_BLACK);
	init_pair(14, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(15, COLOR_BLUE, COLOR_MAGENTA);
	init_pair(16, COLOR_GREEN, COLOR_BLUE);
	
	
	// Find upper left corner
	int y = y_0 + squareHeight * (pos / 4) + 1;
	int x = x_0 + squareWidth * (pos % 4);

	ss.str("");
	if (b.getVal(pos) == 0) {
		move(y,x + 1);
		addstr( EMPTY_STRING );
		move(y + 1, x + 1);
		addstr( EMPTY_STRING );
		move(y - 1, x + 1);
		addstr( EMPTY_STRING );
	}
	else{
		int colorPairValue = (int) (log(b.getVal(pos)) / log(2));
		if (b.getVal(pos) > 0 ) {
			attron(COLOR_PAIR( (colorPairValue % 16) + 1) );
		}
		ss << b.getVal(pos);
		int length = ss.str().length();
		int diff = (squareWidth - length)/2;
		
		// Clear square to color
		move(y,x + 1);
		addstr( EMPTY_STRING );
		move(y + 1, x + 1);
		addstr( EMPTY_STRING );
		move(y - 1, x + 1);
		addstr( EMPTY_STRING );
		move(y, x + 1);
		for (int i = 0; i < diff - 1; i++)
			addch(' ');
		
		addstr( (ss.str()).c_str() );

		for (int i = 0; i < diff - 1; i++)
			addch(' ');
		if (b.getVal(pos) > 0 ) {
			attroff(COLOR_PAIR( (colorPairValue % 16) + 1) );
		}
	}
}

void drawBoard(board_2048& b) {
	// Draw Border
	// Horizontal Lines
	move(score_y, score_x);
	ss.str("");
	ss << b.getScore() << "     ";
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	addstr( "SCORE: " );
	addstr( (ss.str()).c_str());
	// Add High Score
	ss.str("");
	ss << highScore << "         ";
	move(score_y + 1, score_x);
	addstr( "HIGHSCORE: " );
	addstr( ss.str().c_str());
	
	// Add GAme Number
	ss.str("");
	ss << "GAME NUMBER: " << gameNumber;
	move(score_y + 2, score_x);
	addstr(ss.str().c_str());
	
	attroff(COLOR_PAIR(1));
	for (int j = 0; j < 5; j++) {
		move(y_0 - 1 + squareHeight*j, x_0);
		for (int i = 0; i < 4 * squareWidth; i++ )
			if ( i % squareWidth == 0) {
				if (j == 0) addch(ACS_TTEE);
				else if (j == 4) addch(ACS_BTEE);
				else addch(ACS_HLINE);
			}
			else
				addch(ACS_HLINE);
	}
	// Vertical Lines
	for (int j = 0; j < 4*squareHeight; j++) {
		for (int i = 0; i < 5; i++){
			move(y_0 + j, x_0 + i * squareWidth);
			if (j % squareHeight == squareHeight - 1) {
				if (i == 0) addch(ACS_LTEE);
				else if (i == 4) addch(ACS_RTEE);
				else addch(ACS_PLUS);
			}
			else
				addch(ACS_VLINE);
			
		}
	}
	// Draw Corners
	move(y_0 - 1, x_0);
	addch(ACS_ULCORNER);
	move(y_0 - 1, x_0 + 4*squareWidth);
	addch(ACS_URCORNER);
	move(y_0 + 4*squareHeight - 1, x_0);
	addch(ACS_LLCORNER);
	move(y_0 + 4*squareHeight - 1, x_0 + 4 * squareWidth);
	addch(ACS_LRCORNER);
	
	for (int i = 0; i < 16; i++) {
		drawSquare(i, b);
	}
	move(HEIGHT, WIDTH);
}

void nCursesInit() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	
	EMPTY_STRING = new char[squareWidth];
	for (int i = 0; i < squareWidth - 1; i++)
		EMPTY_STRING[i] = ' ';
} 

void initColorPairs() {
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_RED);
	init_pair(3, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(4, COLOR_BLUE, COLOR_YELLOW);
	init_pair(5, COLOR_YELLOW, COLOR_BLUE);
	init_pair(6, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(7, COLOR_RED, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	
	//init_pair(9, COLOR_CYAN, COLOR_MAGENTA);
	//init_pair(10, COLOR_MAGENTA, COLOR_BLUE);
	//init_pair(11, COLOR_BLUE, COLOR_GREEN);
	//init_pair(12, COLOR_GREEN, COLOR_RED);
	//init_pair(13, COLOR_RED, COLOR_BLACK);
	//init_pair(14, COLOR_MAGENTA, COLOR_CYAN);
	//init_pair(15, COLOR_BLUE, COLOR_MAGENTA);
	//init_pair(16, COLOR_GREEN, COLOR_BLUE);
}
int main(int argc, const char* argv[]) {
	board_2048 board = board_2048();
	board_2048 board2 = board_2048(board);
	stringstream ss;
	board.init();
	nCursesInit();
	// TEMP
	attron(COLOR_PAIR(3));
	bool repeat = true;
	char ch;
	// AI loop
	if (usingAI) {
		int currentScore;
		for (gameNumber = 1;gameNumber <= numberOfGames; gameNumber++) {
			currentScore = board.newGame();
			if (currentScore > highScore) highScore = currentScore;
			direction_t d;
			while (true) {
				drawBoard(board);
				d = rowfillAI.chooseMove(board);

				move(0,0);
				switch (d) {
					case UP:
						addstr("UP    ");
						break;
					case DOWN:
						addstr("DOWN  ");
						break;
					case LEFT:
						addstr("LEFT  ");
						break;
					case RIGHT:
						addstr("RIGHT ");
						break;
					default:
						addstr("NONE  ");
						break;
				}		
				refresh();
				usleep(SLEEP_TIME);
				
				board.move(d);
				if (d == NONE) break;
			}
			drawBoard(board);
			refresh();
			
		}
		if (board.getScore() > highScore) highScore = board.getScore();
		cout << highScore;
		cin >> ch;
	}
	// Human Loop
	else while (repeat) {
		drawBoard(board);
		ch = getch();
		switch (ch) {
			case 'q':
			case 'Q':
			case 'x':
			case 'X':
				repeat = false;
				break;
			case 'w':
			case 'W':
			case KEY_UP:
				board.move(UP);
				move(21, 0);
				addch('U');
				break;
			case 'S':
			case 's':
			case KEY_DOWN:
				board.move(DOWN);
				move(21, 0);
				addch('D');
				break;
			case 'a':
			case 'A':
			case KEY_LEFT:
				board.move(LEFT);
				move(21, 0);
				addch('L');
				break;
			case 'd':
			case 'D':
			case KEY_RIGHT:
				board.move(RIGHT);
				move(21, 0);
				addch('R');
				break;
			default:
				repeat = true;
		}
		refresh();
	}
	drawBoard(board);
	endwin();
	delete[] EMPTY_STRING;
}
