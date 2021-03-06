#include "board_2048.hpp"

/*** 2048 Board Class ***/

board_2048::board_2048(){
	srand(time(NULL));
	for (int i = 0; i < boardsize; i++)
		board[i] = 0;
	score = 0;
	storingGame = false;
}

board_2048::board_2048(unsigned int* entries) {
	srand(time(NULL));
	for (int i = 0; i < boardsize; i++)
		board[i] = entries[i];
	score = 0;
	storingGame = false;

}

board_2048::board_2048(const board_2048& b) {
	srand(time(NULL));
	for (int i = 0; i < boardsize; i++)
		board[i] = b.getValAtPos(i);
	score = b.getScore();
	storingGame = false;
}

board_2048::~board_2048(){
}

/*** Misc ***/
int board_2048::newGame(){
	for (int i = 0; i < 16; i++) board[i] = 0;
	spawnNumber();
	spawnNumber();
	int highscore = score;
	score = 0;
	return highscore;
}
void board_2048::setBoard(gamestate g) {
	for (int i = 0; i < 16; i++) {
		board[i] = g.getBoardValue(i);
	}

	score = g.getScore();
}
void board_2048::getBoard(unsigned int* b){
	for (int i = 0; i < 16; i++) b[i] = board[i];
}

/*** Board Status Functions ***/
bool board_2048::boardIsFull() const {
	for (int i = 0; i < boardsize; i++)
		if (getVal(i) == 0) return false;
	return true;
}

bool board_2048::isValidPos(int pos) const {
	return (0 <= pos && pos < boardsize);
}

bool board_2048::posAtEdge(int pos, direction_t dir) const {
	if (! isValidPos(pos)) return false;
	switch (dir) {
		case NONE:			// Nonsense
			return false;
		case UP:
			return (pos < 4);
		case DOWN:
			return (pos > 11);
		case RIGHT:
			return (pos % 4 == 3);
		case LEFT:
			return (pos % 4 == 0);
		default:
			return false;
	}
}

bool board_2048::dirHoldsSameVal(int pos, direction_t dir) const {
	if (! isValidPos(pos)) return false;	// This is nonsense
	if (posAtEdge(pos, dir)) return false;
	if (dir == NONE) return false;		// This is nonsense
	for (int i = 1; i < 4; i++) {
		/*	1. Check if new position is on board:
		 *		if YES: continue
		 *		if NO:  Return False
		 *	2. Check if the value at new position is the same as value
		 *	   at original position:
		 *		if YES: return true
		 *		if NO: continue
		 *	3. Check if value at new position is empty:
		 *		if YES: continue to next square (via for-looop)
		 *		if NO: return false;
		 */
		if (! isValidPos(pos + i*dir))
			return false;
		if (getValAtPos(pos + i*dir) == getValAtPos(pos))
			return true;
		if (getValAtPos(pos + i*dir) != 0)
			return false;
	}
	return false;
}

bool board_2048::dirIsEmpty(int pos, direction_t dir) const {
	if (! isValidPos(pos)) return false;
	if (! isValidPos(pos + dir)) return false;
	if (dir == NONE) return false;
	if (posAtEdge(pos, dir)) return false;
	if (getValAtPos(pos + dir) == 0) return true;
}

bool board_2048::dirIsValid(int pos, direction_t dir) const {
	return (dirIsEmpty(pos, dir) || dirHoldsSameVal(pos, dir));
}

bool board_2048::posHasMove(int pos) const {
	if (! isValidPos(pos)) return false;
	// Check UP
	if (dirIsValid(pos, UP))return true;
	// Check RIGHT
	if (dirIsValid(pos, RIGHT)) return true;
	// Check DOWN
	if (dirIsValid(pos, DOWN)) return true;
	// Check LEFT
	return (dirIsValid(pos,LEFT));
}

bool board_2048::isValidMove(direction_t dir) const {
	for (int pos = 0; pos < boardsize; pos++)
		if ( dirIsValid(pos, dir) && getValAtPos(pos) != 0)
			return true;
		return false;
}

bool board_2048::hasMove() const {	// NEED TO FINISH!!!!!!!!!!!!!!1
	if (! this->boardIsFull()) return true;
	// Board is full -- check if there is a valid move
	for (int pos = 0; pos < boardsize; pos++)
		if (posHasMove(pos))return true;
	return false;
}

bool board_2048::inCorner(int val) const{
	return (getValAtPos(0) == val || getValAtPos(3) == val ||
		getValAtPos(12) == val || getValAtPos(15) == val);
}

int board_2048::getValAtPos(int pos) const {
	if (isValidPos(pos)) return board[pos];
	return -1;
}

bool board_2048::isGridlocked(){
	int count = 0;
	if (isValidMove(UP)) ++count;
	if (isValidMove(DOWN)) ++count;
	if (isValidMove(LEFT)) ++count;
	if (isValidMove(RIGHT)) ++count;
	return count < 2;
}
bool board_2048::isNormal(){
	if (! inCorner(getHighestVal())) return false;
	std::vector<int> highVals = getPosOfVal(getHighestVal());
	bool isSortedVert = true, isSortedHorz = true;
	for (int i = 0; i < highVals.size(); ++i){
		if (highVals[i] == 0 || highVals[i] == 3 || highVals[i] == 12 || highVals[i] == 15){
			int hdm = 1, vdm = 4;	// Multiply to change iteration direction
			if (highVals[i] == 3 || highVals[i] == 15) hdm = -1;
			if (highVals[i] == 12 || highVals[i] == 15) vdm = -4;
			for (int j = 1; j < 4; ++j)
			{
				if (board[highVals[i] + j * hdm] > board[highVals[i] + hdm*(j - 1)]
					|| board[highVals[i] + hdm*j] == 0) isSortedHorz = false;
				if (board[highVals[i] + vdm * j] > board[highVals[i] + vdm*(j-1)]
					|| board[highVals[i] + vdm * j] == 0) isSortedVert = false;
			}
			if (isSortedVert || isSortedHorz) return true;
		}

	}
	return false;
}

std::vector<unsigned int> board_2048::getSortedVals(){
	std::vector<unsigned int> vec (board, board + 16);
	std::sort(vec.begin(), vec.end(), reverseComp);
	return vec;
}

int board_2048::normality(){
	if (! inCorner(getHighestVal())) return 0;

	std::vector<int> highVals = getPosOfVal(getHighestVal());
	std::vector<unsigned int> sortedVals = getSortedVals();

	bool isSortedVert, isSortedHorz;
	for (int i = 0; i < highVals.size(); ++i){
		isSortedVert = true; isSortedHorz = true;
		if (highVals[i] == 0 || highVals[i] == 3 || highVals[i] == 12 || highVals[i] == 15){
			int hdm = 1, vdm = 4;	// Multiply to change iteration direction
			int vertNormality = 0, horzNormality = 0;			// Holds normal state
			if (highVals[i] == 3 || highVals[i] == 15) hdm = -1;
			if (highVals[i] == 12 || highVals[i] == 15) vdm = -4;
			for (int j = 1; j < 4; ++j)
			{
				if (board[highVals[i] + j * hdm] > board[highVals[i] + hdm*(j - 1)]
					|| board[highVals[i] + hdm*j] == 0) isSortedHorz = false;
				if (board[highVals[i] + j * hdm] == sortedVals[i]) horzNormality++;
				if (board[highVals[i] + vdm * j] > board[highVals[i] + vdm*(j-1)]
					|| board[highVals[i] + vdm * j] == 0) isSortedVert = false;
				if (board[highVals[i] + vdm * j] == sortedVals[i]) vertNormality++;
			}
			return std::max(vertNormality,horzNormality);
		}

	}
	return 0;
}
bool board_2048::highValIsUnique(){
	return (getPosOfVal(getHighestVal()).size() == 1);
}

std::vector<int> board_2048::getPosOfVal(int val) const {
	std::vector<int> result;
	for (int pos = 0; pos < boardsize; ++pos)
		if (board[pos] == val) result.push_back(pos);
	return result;
}

std::vector<int> board_2048::getPosOfEmpty() const {
	return getPosOfVal(0);
}

int board_2048::getHighestVal() const {
	int highestValue = 0;
	for (int i = 0; i < 16; i++) {
		if (board[i] > highestValue)
			highestValue = board[i];
	}
	return highestValue;
}

int board_2048::column(int col, int row) const {
	return getVal(col + 4 * row);
}

int board_2048::row(int row, int col) const {
	return getVal(4 * row + col);
}

int board_2048::getVal(int pos) const {
	if (! isValidPos(pos)) return -1;
	return board[pos];
}

void board_2048::setVal(int pos, int val) {
	if (isValidPos(pos)) {
		board[pos] = val;
	}
}

int board_2048::getValInDir(int pos, direction_t dir) const {
	if (! isValidPos(pos)) return -1;
	if (! isValidPos(pos + dir)) return -1;
	return getVal(pos + dir);
}

int board_2048::getScore() const { return score; }

int board_2048::numberOfMerges(direction_t dir) const {
	int numberOfMerges = 0;
	if (dir == UP || dir == DOWN) {
		// Looking for merges in columns
		for (int col = 0; col < 4; col++) {
			int previousMergePos = -1;
			for (int pos = 1; pos < 4; pos++){
				for (int possibleMergePos = pos-1; possibleMergePos > previousMergePos; possibleMergePos--) {
					if ( column(col, pos) == 0 ) break;
					if ( column(col, possibleMergePos) != column(col, pos) && column(col, possibleMergePos) != 0) break;
					if ( column(col, pos) == column(col, possibleMergePos)) {
						previousMergePos = pos;
						numberOfMerges++;
						break;
					}
				}
			}
		}
	}
	else if (dir == LEFT || dir == RIGHT) {
		for (int row = 0; row < 4; row++ ) {
			// Looking for merges in rows
			int previousMergePos = -1;
			for (int pos = 1; pos < 4; pos++){
				for (int possibleMergePos = pos-1; possibleMergePos > previousMergePos; possibleMergePos--) {
					if ( this->row(row, pos) == 0 ) break;
					if ( this->row(row, possibleMergePos) != this->row(row, pos) && this->row(row, possibleMergePos) != 0) break;
					if ( this->row(row, pos) == this->row(row,possibleMergePos)) {
						previousMergePos = pos;
						numberOfMerges++;
						break;
					}
				}
			}
		}

	}

	return numberOfMerges;
}

direction_t board_2048::rowOrder(int row) const {
	if (row < 0 || row >= 4) return NONE;
	int base = 4 * row;
	// isOrderedLeft: greatest on the left, least on the right
	// isOrderedRight: greatest on the right, least on the left
	bool isOrderedLeft = true, isOrderedRight = true;
	int highest = getVal(base), lowest = getVal(base);

	for (int i = 1; i < 4; i++) { // 3 comparisons are needed
		// Check low to high first
		if ( getVal(base + i) != 0 ){
			if ( getVal(base + i) >= highest )
				highest = getVal(base + i);
			else
				isOrderedRight = false;
		}

		// Check High To Low nehttp://www.cplusplus.com/reference/sstream/stringstream/str/xt
		if ( getVal(base + i) != 0 ) {
			if (getVal(base + i) <= lowest || lowest == 0)
				lowest = getVal(base + i);
			else
				isOrderedLeft = false;
		}
	}
	if (isOrderedRight) return RIGHT;
	if (isOrderedLeft) return LEFT;
	return NONE;
}

direction_t board_2048::columnOrder(int col) const {
	if (col < 0 || col >= 4) return NONE;
	// isOrderedUp: greatest on top, least on bottom
	// isOrderedDown: greatest on bottom, least on top
	bool isOrderedUp = true, isOrderedDown = true;
	int highest = getVal(col), lowest = getVal(col);

	// Check top to bottom
	for (int i = 4; i < 16; i += 4) {
		// Check low to high first
		if ( getVal(col + i) != 0 ) {
			if ( getVal(col + i) > highest )
				highest = getVal(col + i);
			else
				isOrderedDown = false;
		}

		// Check High to Low next
		if ( getVal(col + i) != 0 ) {
			if ( getVal(col + i) < lowest || lowest == 0 )
				lowest = getVal(col + i);
			else
				isOrderedUp = false;
		}
	}
	if (isOrderedUp) return UP;
	if (isOrderedDown) return DOWN;
	return NONE;
}





/*** Movement/Board Update Functions ***/

void board_2048::spawnNumber() {
	//default to 2
	std::vector<int> empties = getPosOfEmpty();

	int index = empties.at(randInRange(0,empties.size()));
	if (randInRange(0, 10) == 0) board[index] = 4;
	else board[index] = 2;
}

void board_2048::init() {
	spawnNumber();
	spawnNumber();
}




void board_2048::move(direction_t dir) {
	toGameState();
	if (storingGame && isValidMove(dir))
		storedgame.append(this -> toGameState(dir) );
	int pos;
	bool madeAMove= false;
	bool alreadyMerged[16] = {false, false, false, false, false, false, false, false,
							 false, false, false, false, false, false, false, false };
	if (dir == UP || dir == LEFT) {		// dir < 0
		for (int i = 0; i < 16; i++) { 				// Check each square
			while (getVal(i) == 0 && i < 15) i++;	// Find first nonzero entry
			pos = i;		// Store position as we move current square
			// Move position to first non-zero position in dir
			while (isValidPos(pos + dir) && getVal(pos + dir) == 0
					&& ! posAtEdge(pos, dir)) {
				pos += dir;
			}
			// Check to see if we can merge two squares
			if ( isValidPos(pos + dir) && (getVal(pos + dir) == getVal(i)) && getVal(i) != 0
					&& ! posAtEdge(pos, dir) && ! alreadyMerged[pos + dir]) {
				score += getVal(i)*2;
				setVal(pos + dir, getVal(i)*2);	// Double value
				setVal(i, 0);		// Update value at original position to 0
				alreadyMerged[pos + dir] = true;
				madeAMove = true;
			}
			else if (pos != i && getValAtPos(i) != 0) {	// No score but we move a piece
				setVal(pos, getVal(i));
				setVal(i, 0);
				madeAMove = true;
			}
		}
	}
	else if (dir == DOWN || dir == RIGHT) {
		for (int i = 15; i >= 0; i--) {
			// Find next non-zero value
			while (getVal(i) == 0 && i > 0) i--;
			pos = i;		// Store position as we move current squre
			// Move position to first non-zero position
			while (isValidPos(pos + dir) && getVal(pos + dir) == 0 && ! posAtEdge(pos, dir)) {
				pos += dir;
			}
			// Check to see if we can merge two squares
			if ( isValidPos(pos + dir) && getVal(pos + dir) == getVal(i)
					&& ! posAtEdge(pos, dir) && ! alreadyMerged[pos + dir]) {
				score += getVal(i) * 2;
				setVal(pos + dir, getVal(i)*2);	// Double Value
				setVal(i, 0);
				alreadyMerged[pos + dir] = true;
				madeAMove = true;
			}
			else if (pos != i && getValAtPos(i) != 0) {
				setVal(pos, getVal(i));
				setVal(i, 0);
				madeAMove = true;
			}
		}
	}
	if(madeAMove) spawnNumber();
}

void board_2048::moveNoSpawn(direction_t dir) {
	toGameState();
	if (storingGame && isValidMove(dir))
		storedgame.append(this -> toGameState(dir) );
	int pos;
	bool madeAMove= false;
	bool alreadyMerged[16] = {false, false, false, false, false, false, false, false,
							 false, false, false, false, false, false, false, false };
	if (dir == UP || dir == LEFT) {		// dir < 0
		for (int i = 0; i < 16; i++) { 				// Check each square
			while (getVal(i) == 0 && i < 15) i++;	// Find first nonzero entry
			pos = i;		// Store position as we move current square
			// Move position to first non-zero position in dir
			while (isValidPos(pos + dir) && getVal(pos + dir) == 0
					&& ! posAtEdge(pos, dir)) {
				pos += dir;
			}
			// Check to see if we can merge two squares
			if ( isValidPos(pos + dir) && (getVal(pos + dir) == getVal(i)) && getVal(i) != 0
					&& ! posAtEdge(pos, dir) && ! alreadyMerged[pos + dir]) {
				score += getVal(i)*2;
				setVal(pos + dir, getVal(i)*2);	// Double value
				setVal(i, 0);		// Update value at original position to 0
				alreadyMerged[pos + dir] = true;
				madeAMove = true;
			}
			else if (pos != i && getValAtPos(i) != 0) {	// No score but we move a piece
				setVal(pos, getVal(i));
				setVal(i, 0);
				madeAMove = true;
			}
		}
	}
	else if (dir == DOWN || dir == RIGHT) {
		for (int i = 15; i >= 0; i--) {
			// Find next non-zero value
			while (getVal(i) == 0 && i > 0) i--;
			pos = i;		// Store position as we move current squre
			// Move position to first non-zero position
			while (isValidPos(pos + dir) && getVal(pos + dir) == 0 && ! posAtEdge(pos, dir)) {
				pos += dir;
			}
			// Check to see if we can merge two squares
			if ( isValidPos(pos + dir) && getVal(pos + dir) == getVal(i)
					&& ! posAtEdge(pos, dir) && ! alreadyMerged[pos + dir]) {
				score += getVal(i) * 2;
				setVal(pos + dir, getVal(i)*2);	// Double Value
				setVal(i, 0);
				alreadyMerged[pos + dir] = true;
				madeAMove = true;
			}
			else if (pos != i && getValAtPos(i) != 0) {
				setVal(pos, getVal(i));
				setVal(i, 0);
				madeAMove = true;
			}
		}
	}
	if(madeAMove) spawnNumber();
}

gamestate board_2048::toGameState() {
	board_t b;
	for (int pos = 0; pos < 16; ++pos){
		b.values[pos] = board[pos];
	}
	gamestate result(b, score);
	return result;
}
gamestate board_2048::toGameState(direction_t d){
	board_t b;
	for (int pos = 0; pos < 16; ++pos){
		b.values[pos] = board[pos];
	}
	gamestate result(b, score, d);
	return result;
}

void board_2048::toFile(std::string fname) {
	storedgame.toFile(fname);
}
bool board_2048::loadFile(std::string fname) {
	storedgame.parseFile(fname);
}

bool board_2048::loadCurrentState() {
	setBoard(storedgame.getCurrentState());

	return true;
}
bool board_2048::incrementState(){
	return storedgame.increment();
}
bool board_2048::incrementState(int n){
	for (int i = 0; i < n; ++i) storedgame.increment();
	return true;
}
bool board_2048::decrementState(){
	return storedgame.decrement();
}
bool board_2048::decrementState(int n){
	for (int i = 0; i < n; ++i ) storedgame.decrement();
	return true;
}

bool board_2048::storedGameIsEmpty() {
	return storedgame.isEmpty();
}
