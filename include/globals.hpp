/* Some global variables that will be useful to access throughout the program
 * Mainly pertain to AIs
 */

#ifndef _GLOBALS_HPP
#define _GLOBALS_HPP
extern unsigned int  EVAL_DEPTH;
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
#endif
