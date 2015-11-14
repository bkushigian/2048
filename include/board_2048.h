#ifndef BOARD_2048
#define BOARD_2048

//#define BOARD_DBG

#include <iostream>
#include <stdlib.h>			// rand(), srand()
#include <time.h>			// to seed srand()
#include "array_t.h"

// Some enums to pass to various helper functions
enum direction_t {NONE = 0, UP   = -4,  DOWN   = 4,  LEFT   = -1, RIGHT   = 1,
							UP_2 = -8,  DOWN_2 = 8,  LEFT_2 = -2, RIGHT_2 = 2,
							UP_3 = -12, DOWN_3 = 12, LEFT_3 = -3, RIGHT_3 = 3};

/* 2048 Board Class */

class board_2048 {
protected:
	unsigned int board[16];
	unsigned int score;
	static const int boardsize = 16;
public:
/*** Constructors/Destructors ***/
	board_2048();
	board_2048(unsigned int* entries);
	board_2048(const board_2048& b);
	~board_2048();
/*** Misc ***/
	int newGame();
	void getBoard(unsigned int* b);
/*** Board Status Functions ***/
	bool boardIsFull() const;				// Tell if board is full
	bool isValidPos(int pos) const;	// Is this a valid position?
	bool posAtEdge(int pos, direction_t dir) const;		// Check if position pos is all the way to the dir side
	bool dirHoldsSameVal(int pos, direction_t dir) const;		// Check if the next value in dir from position is the same as value at pos
	bool dirIsEmpty(int pos, direction_t dir) const;		// Check if direction dir from position pos is empty
	bool dirIsValid(int pos, direction_t dir) const;	// Find out if position can move in dir
	bool posHasMove(int pos) const;	// Tell if pos has a valid move
	bool isValidMove(direction_t dir) const;	// Check if dir is a valid move on whole board
	bool hasMove() const;				// Tell if board has a valid move
	bool inCorner(int val) const;		// Tell if value val is in corner
	int getValAtPos(int pos) const;	// Get value val at position pos
	array_t& getPosOfVal(int val) const;	// Returns an array of integers {totalNumber, p1, p2, ..., ptotalNumber}
	array_t& getPosOfEmpty() const;		// Return array_t of positions of all empty values
	int getHighestVal() const;		// Returns highestValue
	int getVal(int pos) const;		// Return value at position pos
	int column(int col, int row) const;
	int row(int row, int col) const;
	void setVal(int pos, int val);	// Set board value
	int getValInDir(int pos, direction_t dir) const;		// Get the value of board to left/right/up/down from pos
	int getScore() const;


	int numberOfMerges(direction_t dir) const;	// Get number of merges in direction_t dir
	/* Check if row is ordered - ignore empty spaces
	 * returns: LEFT if row is ordered large to small;
	 * returns: RIGHT if row is ordered small to large
	 * returns: NONE if row is not in order */
	direction_t rowOrder(int row) const;
	/* Check if column is ordered - ignore empty spaces.
	 * returns: UP if column is ordered from largest to smallest;
	 * returns: DOWN if column is ordered from smallest to largest;
	 * returns: NONE if column is not in order */
	direction_t columnOrder(int col)const;

	bool rowIsFull(int row) const;	// Return true if row has all non-zero entries, false otherwise
	bool columnIsFull(int col) const;	// Return true if col has all non-zero entries, false otherwise

	int getRowWithHighVal();			// Return 0-3 for which row has the highest value
	int getColumnWithHighVal();			// Return 0-3 for column with high val

	bool rowCanMerge(int row);	// Return trrue if the row can merge, false otherwise
	bool columnCanMerge(int col);	// Return true if col can merge, false otherwise

	bool isGridlocked();		// Return true if board has n rows or n columns totally filled and 4-n rows (or columns) totally empty, with no possible merges

	bool squareIsBlocked(int pos);	// Return true if all adjacentvalues are greater than val(pos)
	int getNumberOfEmptySquares();	//



/*** Random Number Functions ***/
	int randInRange(int min, int max) {
		return rand() % (max - min) + min;
	}
/*** Movement/BoardUpdate Functions ***/
	void spawnNumber();
	void init();

	void move(direction_t dir);
};


#endif
