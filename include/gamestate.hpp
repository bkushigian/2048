#ifndef _GAMESTATE_HPP
#define _GAMESTATE_HPP
#include "board_t.hpp"
#include "direction_t.hpp"
#include <string>
#include <sstream>

class gamestate {
public:
   /* Constructors */
   gamestate();
   gamestate(board_t b, unsigned int s);
   gamestate(board_t b, unsigned int s, direction_t m);
   gamestate(gamestate const& other);
   /** gamestate(unsigned int b[])
   *  Constructor. Takes board of length 16
   */
   gamestate(unsigned int b[], unsigned int s);
   gamestate(unsigned int b[], unsigned int s, direction_t m);
   /* Getters/Setters */
   board_t getBoard() const;
   unsigned int getBoardValue(int n);
   void setBoard(board_t b);
   unsigned int getScore() const;
   void setScore(unsigned int s);
   direction_t getMove() const { return move;}
   void setMove(direction_t m) {move = m;}
   void setComment(std::string c){ comment = c;}
   std::string getComment(){ return comment; }

   std::string toString();
private:
   mutable unsigned int board[16];     // The board of gamestate
   unsigned int score;                 // The score of gamestate
   direction_t move;                   // Next move
   std::string comment;
};
#endif
