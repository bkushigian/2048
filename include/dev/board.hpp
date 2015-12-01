/* A new and improved board class. Higher efficiency, smaller set of methods.
 * This will not be integrated until sufficient testing has ensued. */

 #ifndef _BOARD_HPP
 #define _BOARD_HPP

 #include <iostream>

enum dir_t 	{	NONE 	= 0,
				UP 		= -4,
				DOWN 	= 4,
				LEFT 	= 1,
				RIGHT	= -1
			};

typedef unsigned long long 		ullong_t;
typedef unsigned char			tile_t;
typedef unsigned char			ubyte_t;
typedef unsigned short			ushort_t;
typedef ubyte_t					pos_t;

extern const ubyte_t tileMap[16]{   0b00000000,
                        0b10000000,
                        0b01000000,
                        0b11000000,
                        0b00100000,
                        0b10100000,
                        0b01100000,
                        0b11100000,
                        0b00010000,
                        0b10010000,
                        0b01010000,
                        0b11010000,
                        0b00110000,
                      0b10110000,
                        0b01110000,
                        0b11110000
                    }; 
class board {
protected:
	ullong_t b;							// Holds board
public:
	/*** Constructors ***/
	board() { b = 0; }
	//board(& board) = default;
	/*** Operators ***/
	tile_t  operator[] (pos_t p) const;
	/*** Methods ***/
	bool 	move(dir_t d);
	bool	up();
	bool	down();
	bool	left();
	bool	right();
	void  	set(pos_t p, ullong_t v);
	ullong_t	getBoard();
	//board	moveResult(dir_t d);
};

void drawBoard(board b);
void drawBoardBin(board b);
 #endif
