#include "Monster.h"
// Default Constructor
Monster::Monster(){
    m_name = ""; // Initialize m_name
    m_screamPL = 0; // Initialize m_screamPL
}
// Default Deconstructor
Monster::~Monster(){
}
// setName Setter
void Monster::setName(string name){
    m_name = name; // Set parameter as Monster's name
}
// getName Getter
string Monster::getName(){
    return m_name; // Return Monster's name
}
// setScreamPL Setter
void Monster::setScreamPL(int screamPL){
    m_screamPL = screamPL; // Set parameter a Monster's scream power level
}
// setScreamPL Getter
int Monster::getScreamPL(){
    return m_screamPL; // Return Monster's scream power level
}
// compareScreamPL Function
string Monster::compareScreamPL(Monster monster){
    if (m_screamPL >= monster.getScreamPL()){ // If Monster's scream power level is greater than or equal to parameter Monster's scream level
        return "Winner"; // Return "Winner" string
    }
    if ((m_screamPL < monster.getScreamPL())){ // If Monster's scream power level is less than parameter Monster's scream level
        return "Loser"; // Return "Loser" string
    }
}
