#ifndef _LOAD_PARAMS_HPP
#define _LOAD_PARAMS_HPP
#include <map>
#include <fstream>
#include <boost/regex.hpp>
#include <string>
#include <sstream>
#include <iostream>        // for debug

#include "globals.hpp"

/* Some useful variables */

void loadMap();
bool loadParams(std::string fname);


#endif
