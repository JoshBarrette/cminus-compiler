//
// Josh Barrette CSCI 440 HW4
//

// This class parses the parse tree and sends nodes that
// define functions and global vars to methods for handling.

#include "treeParser.h"
#include "functions.h"

using namespace std;

treeParser::treeParser(TreeNode *root) {
    this->populateVectors(root);
    this->nextGlobalAddress = 0;
}

// Populate the vectors that hold global vars and functions.
void treeParser::populateVectors(TreeNode* currentNode) {
    if (currentNode->rule == 40 || currentNode->rule == 41) {
        variables* newThing = new variables(currentNode, "global");
        newThing->memoryAddress = nextGlobalAddress++;
        this->globVec.push_back(newThing);
    } else if (currentNode->rule == 60) {
        this->funVec.push_back(new functionsM(currentNode));
    } else {
        for (int i = 0; i < currentNode->children.size(); i++) {
            populateVectors(currentNode->children.at(i));
        }
    }
}

// Print out the entire table of global vars and functions.
void treeParser::printTable() {
    // Print out globals
    if (this->globVec.size() > 0) {
        cout << "Global Symbol Table" << endl;
        printf("    Name      Type      Size     Scope   Address\n");
        for (int i = 0; i < this->globVec.size(); i++) {
            this->globVec.at(i)->printForTable();
        }
        cout << endl;
    } else {
        cout << "Global Symbol Table -- No Global Symbols" << endl << endl;
    }

    // Print out each individual function
    cout << "Function Table" << endl;
    for (int i = 0; i < this->funVec.size(); i++) {
        this->funVec.at(i)->printTable();
        cout << endl;
    }
}