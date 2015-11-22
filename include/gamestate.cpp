#include "gamestate.hpp"


gamestate::gamestate() {
   for (int pos = 0; pos < 16; ++pos) board[pos] = 0;
   score = 0;
   move = NONE;
}
gamestate::gamestate(board_t b, unsigned int s){
      for (int pos = 0; pos < 16; ++pos) board[pos] = b.values[pos];
      score = s;
      move = NONE;
}
gamestate::gamestate(board_t b, unsigned int s, direction_t m){
      for (int pos = 0; pos < 16; ++pos) board[pos] = b.values[pos];
      score = s;
      move = m;
}
gamestate::gamestate(unsigned int b[], unsigned int s) {
   for (int pos = 0; pos < 16; ++pos) board[pos] = b[pos];
   score = s;
}

gamestate::gamestate(unsigned int b[], unsigned int s, direction_t m) {
   for (int pos = 0; pos < 16; ++pos) board[pos] = b[pos];
   score = s;
   move = m;
}
gamestate::gamestate(gamestate const& other) {
   for (int pos = 0; pos < 16; ++pos)
   board[pos] = other.getBoard().values[pos];
   score = other.getScore();
   move = other.getMove();
}

unsigned int gamestate::getBoardValue(int n){
   if (n >= 0 && n < 16) return board[n];
   return -1;
}

board_t gamestate::getBoard() const{
   return board_t(board);
}
void gamestate::setBoard(board_t b){
   for (int pos = 0; pos < 16; ++pos){
      board[pos] = b.values[pos];
   }
}
unsigned int gamestate::getScore() const {
   return score;
}
void gamestate::setScore(unsigned int s){
   score = s;
}
std::string gamestate::toString() {
   std::stringstream ss;
   ss << "[";
   for (int pos = 0; pos < 15; ++pos) {
      ss << board[pos] << ',';
   }
   ss << board[15] << "]::" << score;
   return ss.str();
}
