//
// Josh Barrette CSCI 440 HW4
//

// This is the class that holds functions and all of their
// params and local variables.

#include "functions.h"
#include <vector>
#include <iostream>
#include "variables.h"
#include "TreeNode.h"

using namespace std;

// Set the name, return type, and address, then populate
// the vectors that hold params and vars.
functionsM::functionsM(TreeNode* functionRoot) {
    this->functionName = functionRoot->text;
    this->returnType = functionRoot->type;
    this->memoryAddress = 0;
    this->populateVectors(functionRoot);
}

// Iterate through each node looking for params and
// local declarations then passing those nodes to
// the methods that handle each kind.
void functionsM::populateVectors(TreeNode* node) {
    if (node->rule == 90 || node->rule == 91) {
        this->paramsVec.push_back(new variables(node, this->functionName));
    } else if (node->rule == 40 || node->rule == 41) {
        this->localsVec.push_back(new variables(node, this->functionName));
    } else {
        // Check children only when we need to
        for (int i = 0; i < node->children.size(); i++) {
            populateVectors(node->children.at(i));
        }
    }
}

// Print out the table of params and local vars for the function.
void functionsM::printTable() {
    // Print the header and params
    printf("Function %s %6s %4d\n", this->functionName.c_str(), this->returnType.c_str(), this->memoryAddress);
    if (this->paramsVec.size() > 0) {
        cout << "   Parameters" << endl;
        printf("    Name      Type      Size     Scope   Address\n");
        for (int i = 0; i < this->paramsVec.size(); i++) {
            this->paramsVec.at(i)->printForTable();
        }
    } else {
        cout << "   Parameters    -- Parameter list is empty." << endl;
    }

    // Print out the local vars
    if (this->localsVec.size() > 0) {
        cout << "   Local Variables" << endl;
        printf("    Name      Type      Size     Scope   Address\n");
        for (int i = 0; i < this->localsVec.size(); i++) {
            this->localsVec.at(i)->printForTable();
        }
    } else {
        cout << "   Local Variables    -- Local Variables list is empty." << endl;
    }
}
