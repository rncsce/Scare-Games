#ifndef TOURNAMENTNODE_H
#define TOURNAMENTNODE_H
#include "Monster.h"

template <typename T> class TournamentNode{
    public:
        // Overloaded Constructor: initializes TournamentNode Object with Monster Object
        TournamentNode(T monster);
        // Virtual Default Deconstructor: deallocates memory used by TournamentNode Object
        virtual ~TournamentNode();
    // Declare TournamentTree as friend class of TournamentNode
    template<typename S> friend class TournamnetTree;
        // m_winner: winner between left and right competitors
        T m_winner; 
        // m_left TournamentNode Pointer: left competitor
        TournamentNode<T>* m_left;
        // m_left TournamentNode Pointer: right competitor
        TournamentNode<T>* m_right;
};
#include "TournamentNode.h"
// Overloaded Constructor
template <typename T> TournamentNode<T>::TournamentNode(T monster){
    m_winner = monster; // Set parameter to TournamentNode's m_winner (the "data" it holds)
    m_left = NULL; // Initialize TournamentNode's m_left pointer
    m_right = NULL; // Initialize TournamentNode's m_right poiner
}
// Default Deconstructor
template <typename T> TournamentNode<T>::~TournamentNode(){
    if (m_left != NULL){ // If TournamentNode's m_left is not NULL
        delete m_left; // DDeallocate memory used my m_left pointer
    }
    if (m_right != NULL){ // If TournamentNode's m_right is not NULL
        delete m_right; // Deallocate memory used my m_right pointer
    }
}
#endif
