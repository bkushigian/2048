#include "gameStorage.hpp"

/* gamestate methods */


/* storedGame Constructors/Destrustors */
storedGame::storedGame() {
   current = 0;
}
storedGame::storedGame(std::string fName){
   parseFile(fName);
   current = 0;
}
storedGame::storedGame(storedGame& other) {
   gamevector = other.gamevector;
   current = 0;
}

/* Getters/Setters/Board Updates */
gamestate storedGame::getState(int n) {
   if (0 <= n && n < gamevector.size()) return gamevector.at(n);
   gamestate g;
   return g;
}
gamestate storedGame::getCurrentState() {
   return gamevector.at(current);
}
board_t storedGame::getBoard(int n) {
   if (0 <= n && n < gamevector.size()) return gamevector.at(n).getBoard();
   return board_t();
}
board_t storedGame::getCurrentBoard(){
   return gamevector.at(current).getBoard();
}
unsigned int storedGame::getScore(int n) {
   if (0 <= n && n < gamevector.size()) return gamevector.at(n).getScore();
   return -1;
}
unsigned int storedGame::getCurrentScore(){
   return gamevector.at(current).getScore();
}
bool storedGame::increment(){
   if ( current < gamevector.size() -1 ) {
      ++current;
      return true;
   }
   return false;
}
bool storedGame::decrement(){
   if ( current > 0 ) {
      --current;
      return true;
   }
   return false;
}
void storedGame::append(gamestate g) {
   gamevector.push_back(g);
}


board_t storedGame::parseBoardString(std::string b){
   unsigned int         bar[16];
   std::stringstream    boardStream(b);
   std::string          cell;
   int pos = 0;
   while (std::getline(boardStream, cell, ',')){
      bar[pos++] = std::atoi(cell.c_str());
   }
   return board_t(bar);
}
/*** File IO ***/
bool storedGame::parseFile(std::string fName){
   static boost::smatch what;        // Store search results
   static boost::regex expr("^([0-9])+::\\[([0-9]+(,[0-9]+){15})\\]::([0-9]+)::(UP|DOWN|LEFT|RIGHT)");
   std::ifstream f(fName.c_str());
   std::string line;
   if (f.is_open()){
      while(getline(f,line)){
         if (line.length() > 0) {
            if (boost::regex_search(line, what, expr))
               append(parseState(line, what));
         }
      }
      return true;
   }
   return false;
}

gamestate storedGame::parseState(std::string line, boost::smatch what) {
   /* Unimplemented, testing compile for regex*/
   /* what[0]: Holds line
    * what[1]: Move Num
    * what[2]: Board
    * what[3]: Residue from regex -- discard
    * what[4]: Score
    * what[5]: Direction */
   int moveNum = std::atoi(std::string(what[1]).c_str());      // move number
   board_t b = parseBoardString(std::string(what[2]).c_str());
   unsigned int s = std::atoi(std::string(what[4]).c_str());
   direction_t moveDir;

   if          (strcmp(std::string(what[5]).c_str(), "UP") == 0)     moveDir = UP;
   else if     (strcmp(std::string(what[5]).c_str(), "DOWN") == 0)   moveDir = DOWN;
   else if     (strcmp(std::string(what[5]).c_str(), "LEFT") == 0)   moveDir = LEFT;
   else if     (strcmp(std::string(what[5]).c_str(), "RIGHT") == 0)  moveDir = RIGHT;
   else                                                 moveDir = NONE;

   return gamestate(b,s,moveDir);
}

std::string storedGame::toString(){
   std::stringstream ss;
   gamestate g;
   int moveNum = 1;
   for (int i = 0; i < gamevector.size(); i++) {
      g = gamevector.at(i);
      ss << moveNum << "::" << '[';
      for (int pos = 0; pos < 15; ++pos)
         ss << g.getBoard().values[pos] << ',';
      ss << g.getBoard().values[15] << "]::" << g.getScore();
      direction_t dir = g.getMove();
      switch (g.getMove()) {
         case UP:
            ss << "::UP\n";
            break;
         case DOWN:
            ss << "::DOWN\n";
            break;
         case RIGHT:
            ss << "::RIGHT\n";
            break;
         case LEFT:
            ss << "::LEFT\n";
            break;
         default:
            ss << "::NONE\n";
            break;
      }

      ++moveNum;
   }
   return ss.str();
}

void storedGame::toFile(std::string fname){
   std::ofstream f(fname.c_str());
   if (f.is_open()) f << this->toString().c_str();
   f.close();
}
