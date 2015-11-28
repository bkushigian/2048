#include "globals.hpp"

unsigned int  EVAL_DEPTH = 2;
bool          BREAK = false;



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
