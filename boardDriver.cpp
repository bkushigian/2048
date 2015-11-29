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
#include <ncurses.h>								/* Display */
#include <sstream>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>								/* exit() */

#include "include/board_2048.hpp"
#include "include/board_t.hpp"
#include "include/gameStorage.hpp"
#include "include/direction_t.hpp"
#include "include/gamestate.hpp"
#include "include/globals.hpp"

#include "AIs/AI.hpp"
#include "AIs/rowFill.hpp"


using namespace std;
/* nCurses variables */
int y_0 = 6, x_0 = 10;			/* Top left of screen */
int squareWidth = 9;				/* Character width of a board square */
int squareHeight = 4;			/* Character height of a board square */
int WIDTH = 4 * squareWidth + 2 * x_0;			/* Width of board */
int HEIGHT = 4 * squareHeight + 2 * y_0;		/* Height of board */
int score_y = 2, score_x = WIDTH/2;				/* Placement of scoreboard */

/* Game Batch Statistics
 * These are for convenient reference while testing AIs
 */
int wins = 0;						/* How many wins since beginning of batch */
int highScore = 0;				/* Highest score since beginning of batch */
unsigned int cummulativeScore = 0; 	/* Total cummulative score since start of batch */
int numberOfGames = 1;			/* Number of games total in batch */
int gameNumber = 0;				/* Current game */


unsigned int sleeptime = 0;	/* Time to sleep between moves. Set to zero since
										 * AI is inefficient.                             */

char* EMPTY_STRING;				/* For creating empty strings while drawing board */
stringstream ss;					/* Store Numbers and strings for nCurses output */

/*** COMMAND LINE OPTIONS ***/
bool usingAI = true;				/* Using AI to play game */
bool usingCurses = true;		/* Using nCurses to display board */
bool storingGame = false;		/* Storing game to output file */
bool loadingFile = false;		/* Loading game */
bool viewingFile = false;		/* Viewing a saved game */
string storedGameName;			/* Location to save game */
string viewedFileName = "storedGames/default.gam";		/* Location to load game for viewing */
string loadedFileName = "storedGames/default.gam";		/* Location to load game for playing */

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
	if (b.getVal(pos) == 0) {		// Draw empty square
		move(y,x + 1);
		addstr( EMPTY_STRING );
		move(y + 1, x + 1);
		addstr( EMPTY_STRING );
		move(y - 1, x + 1);
		addstr( EMPTY_STRING );
	}
	else{									// Not empty
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
void help(){
	cout << "2048 Help \n";
	cout << "\t-h,            --help:           This help menu\n";
	cout << "\t-s [FILENAME], --s [FILENAME]:   Store game to FILENAME on exit\n";
	cout << "\t\tdefault FILENAME: 'storedGames/default.gam'\n";
	cout << "\t-nc,          --nocurses:        Disable ncurses interface - buggy\n";
	cout << "\t-v,           --viewgame:        Load a game for viewing - no play\n";
	cout << "\t-l,           --loadgame:        Load a game for playing. Not implemented\n";
	cout << "\t-n,           --numberofgames:   Number of games for AI to play\n";
	cout << "\t-t,           --sleeptime:       Time between AI moves.\n";
	exit(0);
}

/* This is very bloated. Will refactor. Largely uncommented for now.*/
int main(int argc, const char* argv[]) {
	board_2048 board = board_2048();
	/* Argument Parsing */
	for (int i = 1; i < argc; i++) {
		/* Human Play */
		if ((strcmp(argv[i], "-H") == 0) || (strcmp(argv[i], "--human") == 0))
			usingAI = false;
		/* Store game in file argv[i+1] or default.gam */
		if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--store") == 0)){
			if (i < argc - 1)
				storedGameName = string("storedGames/") + string(argv[++i]);
			else storedGameName = "storedGames/default.gam";
			storingGame = true;
			board.turnStorageOn();
		}
		/* Disable ncurses */
		if ((strcmp(argv[i], "-nc") == 0) || (strcmp(argv[i], "--nocurses") == 0))
			usingCurses = false;
		/* Load game for viewing (no play) */
		if ((strcmp(argv[i], "-v" ) == 0) || (strcmp(argv[i], "--viewgame") == 0)) {
			if (i < argc - 1) viewedFileName = argv[++i];
			else viewedFileName = string("storedGames/") + string("default.gam");
			viewingFile = true;
		}
		/* Load game */
		if ((strcmp(argv[i], "-l" ) == 0) || (strcmp(argv[i], "--load") == 0 )) {
			if (i < argc - 1) loadedFileName = argv[++i];
			else loadedFileName = "storedGames/default.gam";
			loadingFile = true;
		}
		if ((strcmp(argv[i], "-n" ) == 0) || (strcmp(argv[i], "--numberofgames") == 0 ))
			if (i < argc - 1) numberOfGames = atoi(argv[++i]);

		if ((strcmp(argv[i], "-t" ) == 0) || (strcmp(argv[i], "--sleeptime") == 0 ))
			if (i < argc - 1 && atoi(argv[++i]) >= 0) sleeptime = atoi(argv[i]);
		if ((strcmp(argv[i], "-h" ) == 0) || (strcmp(argv[i], "--help") == 0))
			help();
		if ((strcmp(argv[i], "-d" ) == 0) || (strcmp(argv[i], "--depth") == 0 )){
			if (i < argc - 1 && atoi(argv[++i]) >= 0) {
				EVAL_DEPTH = atoi(argv[i]);
				cout << EVAL_DEPTH << endl;
			}
			else return -1;
		}
		if ((strcmp(argv[i], "-b" ) == 0) || (strcmp(argv[i], "--break") == 0 ))
			BREAK = true;
		if ((strcmp(argv[i], "-a" ) == 0) || (strcmp(argv[i], "--automove") == 0 ))
			if (i < argc - 1 && atoi(argv[++i]) >= 1) autoMoves = atoi(argv[i]);
		if ((strcmp(argv[i], "-p" ) == 0) || (strcmp(argv[i], "--precise") == 0 ))
			PRECISE_EVALUATION = true;
		if ((strcmp(argv[i], "-m" ) == 0) || (strcmp(argv[i], "--mode") == 0 ))
			if (++i < argc ){
				if (strcmp(argv[i], "maxempties") == 0) evaluationMode = MAX_EMPTIES;
				else if (strcmp(argv[i], "maxmerges") == 0) evaluationMode = MAX_MERGES;
				else if (strcmp(argv[i], "bastard01") == 0) evaluationMode = BASTARD_01;
				else evaluationMode = MAX_EMPTIES;
			}
	} // End argParse for loop

	if (usingCurses){
		board.init();
		nCursesInit();
		// TEMP
		attron(COLOR_PAIR(3));
	}
	bool repeat = true;
	char ch;

	/* Loading Game */
	if (loadingFile) {
		char ch;							// Hold user moves
		bool repeat = true;			// Control display loop
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
