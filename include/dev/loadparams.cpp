#include "loadparams.hpp"


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

   boolMap["PRECISE_EVALUATION"]          = & PRECISE_EVALUATION;
}

bool loadParams(std::string fname){
   ifstream f(fname);
   std::string line;
   static boost::smatch what;
   static boost::regex expr("(double|bool|int)\\s+([a-zA-Z]+\\s*=\\s*)([-+]?[0-9]*\\.[0-9]+|[0-9]+)");
   if (! f.is_open()) return false;
   while (f.getline(f, line)){
      if (line.length() > 0){
         if (boost::regex_search(line, what, expr)) {
            m[std::string(what[0])] = std::atof(std::string(what[1]).c_str());
         }
      }
   }
   f.close();
}
