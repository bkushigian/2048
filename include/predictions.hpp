#ifndef _PREDICTIONS_HPP
#define _PREDICTIONS_HPP

#include "board_2048.hpp"
#include "direction_t.hpp"
#include "board_t.hpp"
#include "globals.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>


direction_t    predChooseMove(board_2048 b, int depth);
double         evalBoard(board_2048 b);
double         evalBoard(board_2048 b, int depth);
double         maxMerges(board_2048 b);
double         maxEmpties(board_2048 b);
double         bastard01(board_2048 b);

#endif
