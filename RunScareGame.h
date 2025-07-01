#ifndef RUNSCAREGAME_H
#define RUNSCAREGAME_H
#include "TournamentTree.h"
#include <sstream>

class RunScareGame{
    public:
        // Overloaded Constructor: initializes RunScareGame
        RunScareGame(const string&  inputFile, const string&  elimination);
        // Default Deconstructor: deallocates memory used by RunScareGame
        ~RunScareGame();
        // runTournament Function: runs the tournament
        void runTournament();
    private: 
        // m_elimination String: whether the tournament is singe or double
        string m_elimination;
        // inFile: file stream to read file
        ifstream inFile;
        // line: string to store file lines
        string line;
        // m_monsters Vector: vector of all monsters in tournament
        vector<Monster> m_monsters;
        // tournamentTree TournamentTree: tournament tree of monsters
        TournamentTree<Monster> tournamentTree;
};
#endif
