#include "RunScareGame.h"
#include <string>
using namespace std;

int main(int argc, char** argv){

    string inputFile = argv[1];
    string elimination = argv[2];
    RunScareGame runScareGame(inputFile, elimination);
    runScareGame.runTournament();

    return 0;
}
