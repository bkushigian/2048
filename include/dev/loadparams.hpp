#ifndef _LOAD_PARAMS_HPP
#define _LOAD_PARAMS_HPP
#include <map>
#include <fstream>
#include <boost/regex>

std::map<std::string, double*>   doubleMap;
std::map<std::string, int*>      intMap;
std::map<std::string, bool*>     boolMap;


void loadMap();
bool loadParams(std::string fname);


#endif
