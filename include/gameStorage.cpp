#include "gameStorage.hpp"

/* gamestate methods */
gamestate::gamestate(array_t b, unsigned int s, direction_t m, gamestate* p, gamestate* n){
      for (int pos = 0; pos < 15; ++pos) board[pos] = b.values[pos];
      score = s;
      move = m;
      prev = p;
      next = n;
}
array_t gamestate::getBoard(){
   array_t result(16);
   for (int pos = 0; pos < 16; ++pos){
      result.values[pos] = board[pos];
   }
   return result;
}
void gamestate::setBoard(array_t b){
   for (int pos = 0; pos < 16; ++pos){
      board[pos] = b.values[pos];
   }
}
unsigned int gamestate::getScore(){
   return score;
}
void gamestate::setScore(unsigned int s){
   score = s;
}
gamestate* gamestate::getNext(){
   return next;
}
void gamestate::setNext(gamestate* n){
   next = n;
}
gamestate* gamestate::getPrev(){
   return prev;
}
void gamestate::setPrev(gamestate* p){
   prev = p;
}


/* storedGame methods */
storedGame::storedGame(std::string fName){
   head = NULL;
   tail = NULL;
   curr = NULL;
   parseFile(fName);
}

void storedGame::parseFile(std::string fName){
   std::ifstream f(fName.c_str());
   std::string line;
   if (f.is_open()){
      while(getline(f,line)){
         if (line.length() > 0) {
            if (line.at(0) != '#')
               append(parseState(line));
         }
      }
   }
}

gamestate* storedGame::parseState(std::string line) {
   /* Unimplemented, testing compile for regex*/
   int n;      // move number
   array_t b(16);
   unsigned int s = 1234;
   direction_t m = UP;
   std::string re_validLine = "^[0-9]+::\\[[0-9]+(,[0-9]+){15}\\]::[0-9]+::(UP|DOWN|LEFT|RIGHT)";
   gamestate* result = new gamestate(b,s,m,NULL,NULL);
   return result;
}
storedGame::~storedGame(){
   if (head != NULL){
      gamestate* n = head->getNext();
      curr = head;
      while (n != NULL){
         delete curr;
         curr = n;
         n = n->getNext();
      }
      delete curr;
   }
}

bool storedGame::prev(){
   if (curr == NULL) return false;
   if (curr->getPrev() == NULL) return false;
   curr = curr->getPrev();
   return true;
}

bool storedGame::next(){
   if (curr == NULL) return false;
   if (curr->getNext() == NULL);
   curr = curr->getNext();
   return true;
}

array_t storedGame::getBoard(){
   return curr->getBoard();
}
unsigned int storedGame::getScore(){
   return curr->getScore();
}

void storedGame::append(gamestate* g) {
   if (head == NULL){
      head = g;
      tail = head;
      curr = head;
      head->setPrev(NULL);
      head->setNext(NULL);
   }
   else {
      g->setPrev(tail);
      tail->setNext(g);
      tail = g;
   }
}
