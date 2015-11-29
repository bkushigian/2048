#include "globals.hpp"

int EVAL_DEPTH                  = 2;
bool BREAK                      = false;



double normalNotGridlocked      = 4.5;
double highValInCorner          = 4.7;
double numberOfMergesFactor     = 0.5;
double numberOfEmptiesFactor    = 1.2;
double scoreFactor              = 0.2;
double badEmptyValue            = 2.3;
double twosFactor               = 1.0;
double foursFactor              = 0.1;
double normalFactor             = 2.0;

bool    PRECISE_EVALUATION      = false;   // true -> evaluate fours.

int    autoMoves                = 5;        // Moves computer does automatically before AI begins
int MIN_EMPTIES                 = 4;

EVAL_MODE evaluationMode        = MAX_EMPTIES;



/* Some other variables */
/* Game Batch Statistics
 * These are for convenient reference while testing AIs
 */
int wins = 0;						/* How many wins since beginning of batch */
int highScore = 0;				/* Highest score since beginning of batch */
unsigned int cummulativeScore = 0; 	/* Total cummulative score since start of batch */
int numberOfGames = 1;			/* Number of games total in batch */
int gameNumber = 0;				/* Current game */


unsigned int sleeptime = 0;	/* Time to sleep between moves. Set to zero since
		      								 * AI is inefficient.


/*** Command Line Options ***/
bool usingAI = true;				/* Using AI to play game */
bool usingCurses = true;		/* Using nCurses to display board */
bool storingGame = false;		/* Storing game to output file */
bool loadingFile = false;		/* Loading game */
bool viewingFile = false;		/* Viewing a saved game */
std::string storedGameName;			/* Location to save game */
std::string viewedFileName = "storedGames/default.gam";		/* Location to load game for viewing */
std::string loadedFileName = "storedGames/default.gam";		/* Location to load game for playing */
