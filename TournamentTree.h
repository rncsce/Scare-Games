#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H
#include "TournamentNode.h"
#include <vector>
#include <iostream>
#include <fstream>

template <typename T> class TournamentTree{
    public:
        // Default Constructor: initializes TournamentTree object
        TournamentTree();
        // Virtual Default Deconstructor: deallocated memory by TournamentTree object
        virtual ~TournamentTree();
        // Overloaded buildTournamentTree Function: sets up single or double tournament trees
        void buildTournamentTree(string elimination, vector<T> monsters, const string& fileName);
    private:
        // m_root TournamentNode Pointer: root of TournamentTree
        TournamentNode<T>* m_root;
        // m_1stWinner TournamentNode Pointer: winner (root) of first round
        TournamentNode<T>* m_1stWinner;
        // m_2ndWinner TournamentNode Pointer: winner (root) of second round
        TournamentNode<T>* m_2ndWinner;
        // m_losers Vector: losers from first round
        vector<T> m_losers;
        // buildTournamentTree Overloaded Function: builds tournament tree
        TournamentNode<T>* buildTournamentTree(vector<T> monsters);
        // buildTournamentTreeHelper Helper Function: helps build levels of tournament tree
        vector<TournamentNode<T>*> buildTournamentTreeHelper(vector<TournamentNode<T>*> tournamentNodes);
        // saveTreeAsDot Function: saves tree as DOT file
        void saveTreeAsDot(const string& filename, TournamentNode<T>* rootNode);
        // saveTreeAsDotHelper Helper Function: helps save tree as DOT file
        void saveTreeAsDotHelper(TournamentNode<T>* node, ofstream& file, int& nodeID);
};
// Default Constructor
template <typename T> TournamentTree<T>::TournamentTree(){
    m_root = NULL; // Initialize m_root pointer
    m_1stWinner = NULL; // Initialize m_1stWinner pointer
    m_2ndWinner = NULL; // Initialize m_2ndWinner pointer
}
// Default Deconstructor
template <typename T> TournamentTree<T>::~TournamentTree(){
    if(m_root != NULL){ // If m_root is not NULL
        delete m_root; // Delete m_root
    }
}
// Overloaded buildTournamentTree Function: 
template <typename T> TournamentNode<T>* TournamentTree<T>::buildTournamentTree(vector<T> monsters){ // Parameter: vector of monsters
    m_losers.clear(); // Clear m_losers vector
    vector<TournamentNode<T>*> tournamentNodes; // Declare vector of TournamentNode pointers, tournamentNodes
    // Creates TournamentNodes for each Monster in tournament
    for (int i = 0; i < monsters.size(); i++){ // Iterate for vector's size
        TournamentNode<T>* newNode = new TournamentNode<T>(monsters[i]); // Initialize new TournamentNode pointer with Monster at current index as newNode
        tournamentNodes.push_back(newNode); // Add newNode to tournamentNodes vector
    }
    vector<TournamentNode<T>*> winner = buildTournamentTreeHelper(tournamentNodes); // Call buildTournamentTreeHelper, assign returned vector of TournamentNode pointers as winner (last node in returned vector is the winner)
    return winner[0]; // Return the TournamentNode pointer in the returned vector
}
// buildTournamentTree Helper Function: 
template <typename T> vector<TournamentNode<T>*> TournamentTree<T>::buildTournamentTreeHelper(vector<TournamentNode<T>*> tournamentNodes){ // Parameter: vector of TournamentNode pointers
    vector<TournamentNode<T>*> temp; // Declare vector of TournamentNode pointers, temp
    if (tournamentNodes.size() == 1){ // If there is one node in tournamentNode
        return tournamentNodes; // Return tournamentNodes (the winner)
    }
    for(int i = 0; i < tournamentNodes.size(); i += 2){ // Iterate tournamentNodes by 2's
        if ((i + 1) >= tournamentNodes.size()){ // If the current index + 1 is greater than tournamentNodes' size and would be out of bounds (odd number of tournamentNodes)
            temp.push_back(tournamentNodes[i]); // Add tournament node to back to temp vector
        } else if ((tournamentNodes[i] -> m_winner).compareScreamPL(tournamentNodes[i + 1] -> m_winner) == "Winner"){ // If compareScreamPL function at tournamentNodes' current index's TournamentNode's winner, compared to current index + 1's TournamentNode's winner returns "Winner"
            TournamentNode<T>* newNode = new TournamentNode<T>(tournamentNodes[i] -> m_winner); // Initialize new TournamentNode pointer with tournamentNodes' current index's TournamentNode's winner as newNode
            newNode -> m_left = tournamentNodes[i]; // Assign newNode's left pointer with TournamentNode at current index
            newNode -> m_right = tournamentNodes[i + 1]; // Assign newNode's right pointer with TournamentNode at (current index + 1)
            m_losers.push_back(tournamentNodes[i + 1] -> m_winner); // Add TournamentNode at (current index + 1) to m_losers vector
            temp.push_back(newNode); // Add newNode temp
        } else if ((tournamentNodes[i] -> m_winner).compareScreamPL(tournamentNodes[i + 1] -> m_winner) == "Loser"){ // If compareScreamPL function at tournamentNodes vector's current index's TournamentNode's winner, compared to current index + 1's TournamentNode's winner returns "Loser"
            TournamentNode<T>* newNode = new TournamentNode<T>(tournamentNodes[i + 1] -> m_winner);
            newNode -> m_left = tournamentNodes[i + 1]; // Assign newNode's left pointer with TournamentNode at (current index + 1)
            newNode -> m_right = tournamentNodes[i]; // Assign newNode's right pointer with TournamentNode at current index
            m_losers.push_back(tournamentNodes[i] -> m_winner); // Add TournamentNode at current index to m_losers vector
            temp.push_back(newNode); // Add newNode temp
        } 
    }
    return buildTournamentTreeHelper(temp); // Recursively call buildTournamentTreeHelper on temp vector of TournamentNodes (tree/tournament level)
}
// Overloaded buildTournamentTree Function: 
template<typename T> void TournamentTree<T>::buildTournamentTree(string elimination, vector<T> monsters, const string& fileName){ // Parameters: single or double, vector of starting monsters, output filename
    if (elimination == "single" || elimination == "Single"){ // If elimination is either "single" or "Single"
        m_1stWinner = buildTournamentTree(monsters); // Call buildTournamentTree Function (vector of monsters parameter), assign m_1stWinner with returned TournamentNode from buildTournamentTree function
        m_root = m_1stWinner; // Assign m_root with m_1stWinner
    } else if (elimination == "double" || elimination == "Double"){ // If elimination is either "double" or "Double"
        m_1stWinner = buildTournamentTree(monsters); // Call buildTournamentTree Function (vector of monsters parameter), assign m_1stWinner with returned TournamentNode from buildTournamentTree function
        m_2ndWinner = buildTournamentTree(m_losers); // Call buildTournamentTree Function (vector of monsters parameter), assign m_2ndWinner with returned TournamentNode from buildTournamentTree function
        if(m_1stWinner -> m_winner.compareScreamPL(m_2ndWinner -> m_winner) == "Winner"){ // If m_1stWinner's m_winner compared to m_2ndWinner with compareScreamPL function returns "Winner"
            m_root = new TournamentNode<T>(m_1stWinner -> m_winner);  // Assign m_root with new TournamentNode initialized with m_1stWinner's m_winner
            m_root -> m_left = m_1stWinner; // Assign m_root's left with m_1stWinner Node
            m_root -> m_right = m_2ndWinner; // Assign m_root's right with m_2ndWinner Node
        } else { // If m_1stWinner's m_winner's compared to m_2ndWinner with compareScreamPL function returns "Loser"
            m_root = new TournamentNode<T>(m_2ndWinner -> m_winner);  // Assign m_root with new TournamentNode initialized with m_2ndWinner's m_winner
            m_root -> m_left = m_1stWinner; // Assign m_root's left with m_1stWinner Node
            m_root -> m_right = m_2ndWinner; // Assign m_root's right with m_2ndWinner Node
        }
    }
    saveTreeAsDot(fileName, m_root); // Call saveTreeAsDot function with "TournamentTree.txt" and m_root parameters
}
// Start code from source: DOTFileGeneratorMethods.cpp
// Function to save the tree as a DOT file
template <typename T> void TournamentTree<T>::saveTreeAsDot(const string& filename, TournamentNode<T>* rootNode) {
    ofstream file(filename); // Opens output file stream
    if (!file.is_open()) { // If file is not open
        cerr << "Failed to open file for DOT output: " << filename << "\n"; // Output error statement
        return; // Return
    }
    file << "digraph TournamentTree {\n"; // Output diagraph TournamentTree{ and newline at the beginning of file 
    int nodeID = 0; // Declare and initialize nodeID to 0
    saveTreeAsDotHelper(rootNode, file, nodeID); // Call SaveTreeAsDotHelper
    file << "}\n"; // Output } and newline at the end of file
    file.close(); // Close file
}
// Recursive helper function for DOT file generation
template <typename T> void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, ofstream& file, int& nodeID) {
    if (node == NULL) return; // Base Case: if the node is NULL
    int currentID = nodeID++; // Increment nodeID and declare and initialize as currentID 
    file << "    node" << currentID << " [label=\"" << node -> m_winner.getName() << " (Power: " << node -> m_winner.getScreamPL() << ")\"];\n"; // Output node information
    if (node -> m_left) { 
        int leftID = nodeID; // Declare and initialize leftID as nodeID
        saveTreeAsDotHelper(node -> m_left, file, nodeID); // Recusively call saveTreeAsDotHelper on left node
        file << "    node" << currentID << " -> node" << leftID << ";\n"; // Output node information
    }
    if (node -> m_right) {
        int rightID = nodeID; // Declare and initialize rightID as nodeID
        saveTreeAsDotHelper(node -> m_right, file, nodeID); // Recusively call saveTreeAsDotHelper on right node
        file << "    node" << currentID << " -> node" << rightID << ";\n"; // Output node information
    } 
}
// End code from source: DOTFileGeneratorMethods.cpp
#endif
