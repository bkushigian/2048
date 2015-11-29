/*** boardDriver.cpp
 * This is really a temp file for testing out ideas -- a proof of concept,
 * if you will. This will evenutally be cleaned up and refactored heavily.
 *
 * To Do:
 * 1) Split off display Class
 * 2) Implement a better arg parsing
 * 3) Have better interfacing with saving/loading (all in one)
 * 4) Make a menu
 ***/
#include <iostream>
#include <string.h>
#include <ncurses.h>			/* Display */
#include <sstream>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>			/* exit() */

#include "include/board_2048.hpp"
#include "include/board_t.hpp"
#include "include/gameStorage.hpp"
#include "include/direction_t.hpp"
#include "include/gamestate.hpp"
#include "include/globals.hpp"
#include "include/argparse.hpp"

#include "AIs/AI.hpp"
#include "AIs/rowFill.hpp"


using namespace std;
/* nCurses variables */
int y_0 = 6, x_0 = 10;				/* Top left of screen */
int squareWidth = 9;				/* Character width of a board square */
int squareHeight = 4;				/* Character height of a board square */
int WIDTH = 4 * squareWidth + 2 * x_0;		/* Width of board */
int HEIGHT = 4 * squareHeight + 2 * y_0;	/* Height of board */
int score_y = 2, score_x = WIDTH/2;		/* Placement of scoreboard */


char* EMPTY_STRING;				/* For creating empty strings while drawing board */
stringstream ss;				/* Store Numbers and strings for nCurses output */

rowfillAI rowfillAI;				/* Just temporary from an older build. Still in use */

/* This draws the board without curses. No guarantees on
 * current state of this method - may not be functioning. Was for debugging
 * purposes. Remains in case it can be used later. This remains uncommented. */
void drawBoardNoCurses(board_2048& b){
	for (int i = 0; i < 16; i++) {
		cout.width(7);
		cout << b.getVal(i);
		cout.width(1);
		cout << " | ";
		if (i % 4 == 3)
		cout << '\n';
	}
}


/* This draws a square of the board, given the position. I've had trouble
 * getting the init_pair to stick when calling from outside of this function.
 * This is terribly inefficent since it needs to be called each time I want
 * to draw a square (hundreds if not thousands of times per game). I will look
 * into this eventually */

void drawSquare(int pos, board_2048& b) {
	/* Initialize colors for nCurses use */
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
	if (b.getVal(pos) == 0) {	// Draw empty square
		move(y,x + 1);
		addstr( EMPTY_STRING );
		move(y + 1, x + 1);
		addstr( EMPTY_STRING );
		move(y - 1, x + 1);
		addstr( EMPTY_STRING );
	}
	else{	// Not empty
		int colorPairValue = (int) (log(b.getVal(pos)) / log(2));
		if (colorPairValue < 0 || colorPairValue > 16) colorPairValue = 0;
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


/* draw the board. Appeals to global variables to determine manner to do this
 * (ncurses or otherwise) */
void drawBoard(board_2048& b) {
	if (usingCurses){
		move(score_y, score_x);
		/* Draw the scoreboard */
		ss.str("");
		ss << b.getScore() << "   WINS: " << wins << "     ";
		init_pair(1, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		addstr( "SCORE: " );
		addstr( (ss.str()).c_str());
		// Add High Score
		ss.str("");
		ss << "HIGHSCORE: "<<  highScore << "   " << "AVERAGE: ";
		if (gameNumber > 1) ss <<  cummulativeScore/(gameNumber - 1);
		else ss << 0;
		ss << "        ";
		move(score_y + 1, score_x);
		addstr( ss.str().c_str());

		// Add GAme Number
		ss.str("");

		ss << "GAME " << gameNumber << " OF " << numberOfGames << "  ";
		move(score_y + 2, score_x);
		addstr(ss.str().c_str());

		// Draw Border
		// Horizontal Lines
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
	} // if using curses
	else { // no curses
		for (int i = 0; i < 16; i++) {
			cout.width(7);
			cout << b.getVal(i);
			cout.width(1);
			cout << " | ";
			if (i % 4 == 3)
			cout << '\n';
		}
	} // no curses
}
/* Initialize nCurses. Some basic calls that will get called if nCurses is
 * being used. */
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


/* This currently is not working. I'd like to get it to have global effect
 * but it doesn't. It is commented out to speed up compilation */
 /*
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
*/

/* Print Help function. Need to update functionality for
 *command line arguments */


/* This is very bloated. Will refactor. Largely uncommented for now.*/
int main(int argc, const char* argv[]) {
	char ch;
	board_2048 board = board_2048();
	parseArgs(argc, argv);
	if (storingGame) board.turnStorageOn();

	if (usingCurses){
		board.init();
		nCursesInit();
		// TEMP
		attron(COLOR_PAIR(3));
	}
	bool repeat = true;

	/* Loading Game */
	if (loadingFile) {
		char ch;			// Hold user moves
		bool repeat = true;		// Control display loop
		bool loadError = false;		// See if file failed to load
		int currentScore = 0;		// Maybe unneeded?
		board.loadFile(viewedFileName);
		if (board.storedGameIsEmpty()) {
			loadError = true;
			cout << "Error Loading File\n";

		}
		if (! loadError){
			board.toFile("boardDump.gam");
			board.loadCurrentState();
			drawBoard(board);
			while (repeat){
				drawBoard(board);
				ch = getch();
				switch (ch) {
					case 'q':
					case 'Q':
						repeat = false;
						break;
					case 'a':
						board.decrementState();
						break;
					case 'd':
						board.incrementState();
						break;
					case 's':
						board.decrementState(5);
						break;
					case 'w':
						board.incrementState(5);
						break;
					case 'e':
						while (board.incrementState()){}
						break;
					case 'b':
						while (board.decrementState()){}
					//case 'c':					// Write comment

				}
				board.loadCurrentState();
				refresh();
			}
		}
	}

	/* AI Loop */
	else if (usingAI) {

		int currentScore;
		for (gameNumber = 1;gameNumber <= numberOfGames; gameNumber++) {
			currentScore = board.newGame();
			if (currentScore > highScore) highScore = currentScore;
			direction_t d;
			while (true) {

				d = rowfillAI.chooseMove(board);
				if (usingCurses){
					drawBoard(board);
					refresh();
					usleep(sleeptime);

					board.move(d);
					if (d == NONE) {
						if (BREAK) getch();
						break;
					}
				} // if using ncurses
				else {
					char ch = 'd';

					drawBoard(board);
					board.move(d);
				}
			} // while (True)
			drawBoard(board);
			cummulativeScore += board.getScore();
			if (usingCurses)
				refresh();
			if (storingGame) {
				board.toFile(storedGameName);
			}

		} // for game number loop
		if (board.getScore() > highScore) highScore = board.getScore();
		if (board.getHighestVal() >= 2048) ++wins;
		refresh();

		cin >> ch;
	} // Using AI


	/* Human Loop */
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
	if (storingGame) board.toFile(storedGameName);
	drawBoard(board);
	endwin();
	std::cout << EVAL_DEPTH << endl;
}
