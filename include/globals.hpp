/* Some global variables that will be useful to access throughout the program
 * Mainly pertain to AIs
 */

#ifndef _GLOBALS_HPP
#define _GLOBALS_HPP

#include <string>


extern int           EVAL_DEPTH;
extern bool          BREAK;

/* AI PARAMETERS */
enum EVAL_MODE {
   MAX_EMPTIES                         = 1,
   MAX_MERGES                          = 2,
   BASTARD_01                          = 3
};

extern double normalNotGridlocked;
extern double highValInCorner;
extern double numberOfMergesFactor;
extern double numberOfEmptiesFactor;
extern double scoreFactor;
extern double normalFactor;

extern int    autoMoves;

extern int MIN_EMPTIES;
extern double badEmptyValue;

extern bool    PRECISE_EVALUATION;   // true -> evaluate fours.
extern double  twosFactor;
extern double  foursFactor;

extern EVAL_MODE evaluationMode;

/* Some other variables */
/* Game Batch Statistics
 * These are for convenient reference while testing AIs
 */
extern int wins;						/* How many wins since beginning of batch */
extern int highScore;				/* Highest score since beginning of batch */
extern unsigned int cummulativeScore; 	/* Total cummulative score since start of batch */
extern int numberOfGames;			/* Number of games total in batch */
extern int gameNumber;				/* Current game */


extern unsigned int sleeptime;	/* Time to sleep between moves. Set to zero since
		      								 * AI is inefficient.


/*** Command Line Options ***/
extern bool usingAI;				/* Using AI to play game */
extern bool usingCurses;		/* Using nCurses to display board */
extern bool storingGame;		/* Storing game to output file */
extern bool loadingFile;		/* Loading game */
extern bool viewingFile;		/* Viewing a saved game */
extern std::string storedGameName;			/* Location to save game */
extern std::string viewedFileName;		/* Location to load game for viewing */
extern std::string loadedFileName;		/* Location to load game for playing */



#endif
