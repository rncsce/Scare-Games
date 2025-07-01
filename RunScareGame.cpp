#include "RunScareGame.h"
// Overloaded Constructor
RunScareGame::RunScareGame(const string&  inputFile, const string&  elimination) : inFile(inputFile){ // Takes in string of file name parameter and initializes file stream
    m_elimination = elimination; // Sets elimination parameter as m_elimination
}
// Default Deconstructor
RunScareGame::~RunScareGame(){
    if(inFile.is_open()){ // If file is open
        inFile.close(); // Close file
    }
}
void RunScareGame::runTournament(){
    if(inFile.is_open()){ // If file is open
        while(getline(inFile, line)){ // While getline access line separated by newline from file
            string name = ""; // Initialize name string variable
            string powerLevel = ""; // Initialize power level string variable
            stringstream ss(line); // Initialize stream stream on line
            getline(ss, name, ','); // While getline accesses characters separated by comma, storing under name
            getline(ss, powerLevel); // While getline accesses characters separated by newline, storing under power level
            Monster monster; // Initialize Monster object
            monster.setName(name); // Set Monster objects name to name variable
            monster.setScreamPL(stoi(powerLevel)); // Set Monster objects name to power level variable
            m_monsters.push_back(monster); // Add monster to m_monsters vector
        }
    } else { // If file is not open
        cout << "Error reading file." << endl; // Output error statement
    }
    tournamentTree.buildTournamentTree(m_elimination, m_monsters, "TournamenTree.txt"); // Call buildTournamentTree on tournamentTree with m_elimination, and m_monsters parameters, and outputfile name
}
