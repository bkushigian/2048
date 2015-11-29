#include "loadparams.hpp"

std::map<std::string, double*>   doubleMap;
std::map<std::string, int*>      intMap;
std::map<std::string, bool*>     boolMap;

void loadMap(){
   doubleMap["normalNotGridlocked"]       = & normalNotGridlocked;
   doubleMap["highValInCorner"]           = & highValInCorner;
   doubleMap["numberOfMergesFactor"]      = & numberOfMergesFactor;
   doubleMap["numberOfEmptiesFactor"]     = & numberOfEmptiesFactor;
   doubleMap["scoreFactor"]               = & scoreFactor;
   doubleMap["badEmptyValue"]             = & badEmptyValue;
   doubleMap["twosFactor"]                = & twosFactor;
   doubleMap["foursFactor"]               = & foursFactor;
   doubleMap["normalFactor"]              = & normalFactor;

   intMap["autoMoves"]                    = & autoMoves;
   intMap["MIN_EMPTIES"]                  = & MIN_EMPTIES;
   intMap["EVAL_DEPTH"]                   = & EVAL_DEPTH;
   boolMap["PRECISE_EVALUATION"]          = & PRECISE_EVALUATION;
}

bool loadParams(std::string fname){
   std::stringstream ss;
   bool b;
   std::ifstream f(fname.c_str());
   std::string line;
   static boost::smatch what;
   static boost::regex expr("(double|bool|int)\\s+([a-zA-Z_]+)\\s*=\\s*([-+]?[0-9]*\\.[0-9]+|[0-9]+)");
   if (! f.is_open()) return false;
   while (getline(f, line)){
      if (line.length() > 0){

         if (boost::regex_search(line, what, expr)) {
            ss.str(""); // In case we want to add bool to boolMap
            if (std::strcmp(std::string(what[1]).c_str(), "double") == 0)
               *doubleMap[std::string(what[2])] = std::atof(std::string(what[3]).c_str());
            else if (std::strcmp(std::string(what[1]).c_str(), "int") == 0)
               *intMap[std::string(what[2])] = std::atoi(std::string(what[3]).c_str());
            else if (std::strcmp(std::string(what[1]).c_str(), "bool") == 0 && (ss >> std::boolalpha >> b) ){
               *boolMap[std::string(what[2])] = b;
            }
            std::cout << std::string(what[2]) << " = " << std::string(what[3]) << std::endl;
         }
      }
   }
   f.close();
   return true;
}
