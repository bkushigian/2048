#ifndef _ARGPARSE_HPP
#define _ARGPARSE_HPP

#include "globals.hpp"
#include "loadparams.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>           /* atoi(), exit() */

using namespace std;

void parseArgs(int argc, const char* argv[]);
void help();
#endif
