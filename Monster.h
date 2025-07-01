#ifndef MONSTER_H
#define MONSTER_H
#include <string>
using namespace std;

class Monster{
    public:
        // Default Constructor: initializes Monster object
        Monster();
        // Default Deconstructor: deallocates memory used by Monster object
        ~Monster();
        // setName Setter: sets Monsters's name
        void setName(string name);
        // getName Getter: gets Monster's name
        string getName();
        // setScreamPL Setter: sets Monster's scream power level
        void setScreamPL(int screamPL);
        // getScreamPL Getter: gets Monster's scream power level
        int getScreamPL();
        // compareScreamPL Function: compares Monster's scream power level to another Monster's scream power level
        string compareScreamPL(Monster monster);
    private:
        // m_name String: Monter's name
        string m_name;
        // m_screamPL Int: Monster's scream power level
        int m_screamPL;
};
#endif
