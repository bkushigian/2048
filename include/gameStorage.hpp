/* Store and load games. */


#ifndef _GAMESTORAGE_HPP
#define _GAMESTORAGE_HPP
#include <fstream>
#include <string>
#include <iostream>
#include <boost/regex.hpp>            // For file parsing
#include <sstream>
#include <vector>
#include "board_t.hpp"
#include "direction_t.hpp"
#include "gamestate.hpp"

static board_t errorBoard((unsigned int []) { -1, -1, -1, -1,
                                       -1, -1, -1, -1,
                                       -1, -1, -1, -1,
                                       -1, -1, -1, -1});

/* A glorified linked list */
class storedGame {

public:
   storedGame();
   storedGame(std::string fName);
   storedGame(storedGame& other);

   /* getters/setters */
   gamestate getState(int n);
   gamestate getCurrentState();
   board_t getBoard(int n);
   board_t getCurrentBoard();
   unsigned int getScore(int n);
   unsigned int getCurrentScore();
   bool increment();
   bool decrement();
   void append(gamestate g);
   void setComment(std::string c) { comment = c;}
   std::string getComment() { return comment;}
   board_t parseBoardString(std::string b);
   bool isEmpty(){
      return (gamevector.size() == 0);
   }

   // file io
   bool parseFile(std::string fName);
   gamestate parseState(std::string line, boost::smatch what);
   std::string toString();
   void toFile(std::string fname);

private:
   std::vector<gamestate> gamevector;
   int current;
   std::string comment;
};

#endif
