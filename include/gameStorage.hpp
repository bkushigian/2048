/* Store and load games. */


#ifndef _GAMESTORAGE_HPP
#define _GAMESTORAGE_HPP
#include <fstream>
#include <string>
#include <boost/regex.hpp>            // For file parsing
#include "array_t.hpp"
#include "board_2048.hpp"


/* gameState is a node in the storedGame linkedList */
class gamestate {
public:
   gamestate(){next = NULL; prev = NULL;}
   gamestate(array_t b, unsigned int s, direction_t m, gamestate* p, gamestate* n);
   array_t getBoard();
   void setBoard(array_t& b);
   unsigned int getScore();
   void setScore(unsigned int s);
   gamestate* getNext();
   void setNext(gamestate* n);
   gamestate* getPrev();
   void setPrev(gamestate* p);
   direction_t getMove();
   void setMove(direction_t m) {move = m;}
private:
   gamestate* next;
   gamestate* prev;
   unsigned int board[16];    // The board of gamestate
   unsigned int score;        // The score of gamestate
   std::string name;
   direction_t move;          // Next move


};

/* A glorified linked list */
class storedGame {

public:
   storedGame(std::string fName);
   ~storedGame();
   // file io
   void parseFile(std::string fName);
   gamestate parseState(std::string line);
   void writeToFile(std::string fName);
   // getters and setters
   gamestate* getHead(){return head;}
   gamestate* getTail(){return tail;}
   gamestate* getCurr(){return curr;}
   void setHead(gamestate* h) { head = h;}
   void setTail(gamestate* t) { tail = t;}
   void setCurr(gamestate* c) { curr = c;}

   bool next();
   bool prev();

   array_t getBoard();
   unsigned int getScore();


   void append(gamestate* g);
private:
   gamestate* head;  // Head of the list (state 0)
   gamestate* tail;  // Tail of the list (state n-1 for an n-state game)
   gamestate* curr;  // Current state being inspected
};

#endif
