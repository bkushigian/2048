#include "argparse.hpp"

void parseArgs(int argc, const char* argv[]){
	for (int i = 1; i < argc; i++) {
		/* Human Play */
		if ((strcmp(argv[i], "-H") == 0) || (strcmp(argv[i], "--human") == 0))
			usingAI = false;
		/* Store game in file argv[i+1] or default.gam */
		if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--store") == 0)){
			if (i < argc - 1)
				storedGameName = string("storedGames/") + string(argv[++i]);
			else storedGameName = "storedGames/default.gam";
			storingGame = true;
		}
		/* Disable ncurses */
		if ((strcmp(argv[i], "-nc") == 0) || (strcmp(argv[i], "--nocurses") == 0))
			usingCurses = false;
		/* Load game for viewing (no play) */
		if ((strcmp(argv[i], "-v" ) == 0) || (strcmp(argv[i], "--viewgame") == 0)) {
			if (i < argc - 1) viewedFileName = argv[++i];
			else viewedFileName = string("storedGames/") + string("default.gam");
			viewingFile = true;
		}
		/* Load game */
		if ((strcmp(argv[i], "-l" ) == 0) || (strcmp(argv[i], "--load") == 0 )) {
			if (i < argc - 1) loadedFileName = argv[++i];
			else loadedFileName = "storedGames/default.gam";
			loadingFile = true;
		}
		if ((strcmp(argv[i], "-n" ) == 0) || (strcmp(argv[i], "--numberofgames") == 0 ))
			if (i < argc - 1) numberOfGames = atoi(argv[++i]);

		if ((strcmp(argv[i], "-t" ) == 0) || (strcmp(argv[i], "--sleeptime") == 0 ))
			if (i < argc - 1 && atoi(argv[++i]) >= 0) sleeptime = atoi(argv[i]);
		if ((strcmp(argv[i], "-h" ) == 0) || (strcmp(argv[i], "--help") == 0))
			help();
		if ((strcmp(argv[i], "-d" ) == 0) || (strcmp(argv[i], "--depth") == 0 ))
			if (i < argc - 1 && atoi(argv[++i]) >= 0)
				EVAL_DEPTH = atoi(argv[i]);
		if ((strcmp(argv[i], "-b" ) == 0) || (strcmp(argv[i], "--break") == 0 ))
			BREAK = true;
		if ((strcmp(argv[i], "-a" ) == 0) || (strcmp(argv[i], "--automove") == 0 ))
			if (i < argc - 1 && atoi(argv[++i]) >= 1) autoMoves = atoi(argv[i]);
		if ((strcmp(argv[i], "-p" ) == 0) || (strcmp(argv[i], "--precise") == 0 ))
			PRECISE_EVALUATION = true;
		if ((strcmp(argv[i], "-m" ) == 0) || (strcmp(argv[i], "--mode") == 0 ))
			if (++i < argc ){
				if (strcmp(argv[i], "maxempties") == 0) evaluationMode = MAX_EMPTIES;
				else if (strcmp(argv[i], "maxmerges") == 0) evaluationMode = MAX_MERGES;
				else if (strcmp(argv[i], "bastard01") == 0) evaluationMode = BASTARD_01;
				else evaluationMode = MAX_EMPTIES;
			}
      if ((strcmp(argv[i], "--loadparams") == 0 )){
			loadMap();
         if (++i < argc){
            cout << "Load Parameters '" << argv[i] << "': " <<  boolalpha << loadParams(argv[i]) << endl;
         }
      }

	} // End argParse for loop
}

void help(){
	cout << "2048 Help \n";
	cout << "\t-h,            --help:           This help menu\n";
	cout << "\t-s [FILENAME], --s [FILENAME]:   Store game to FILENAME on exit\n";
	cout << "\t\tdefault FILENAME: 'storedGames/default.gam'\n";
	cout << "\t-nc,          --nocurses:        Disable ncurses interface - buggy\n";
	cout << "\t-v,           --viewgame:        Load a game for viewing - no play\n";
	cout << "\t-l,           --loadgame:        Load a game for playing. Not implemented\n";
	cout << "\t-n,           --numberofgames:   Number of games for AI to play\n";
	cout << "\t-t,           --sleeptime:       Time between AI moves.\n";
	exit(0);
}
