//
// Josh Barrette CSCI 440 HW4
//

// This class tales in a TreeNode and fills in its data
// depending on what kind of node it is.

#include "variables.h"
#include <string>

using namespace std;

// Fill in the data
variables::variables(TreeNode* node, string scope) {
    if (node->rule == 41) { // local array
        this->name = node->children.at(1)->text;
        this->type = node->children.at(0)->text + "[]";
        this->size = node->children.at(2)->text;
        this->scope = scope;
    } else if (node->rule == 40) { // local int
        this->name = node->children.at(1)->text;
        this->type = node->children.at(0)->text;
        this->size = "1";
        this->scope = scope;
    } else if (node->rule == 90) { // param int
        this->name = node->text;
        this->type = node->type;
        this->size = "1";
        this->scope = scope;
    } else if (node->rule == 91) { // param array
        this->name = node->text;
        this->type = node->type;
        this->size = "1";
        this->scope = scope;
    }

    // Used for debugging
    this->description = this->name + " " + this->type + " "
            + this->size + " " +  this->scope + " " + to_string(this->memoryAddress);
}

// Print out the line corresponding to each variable that
// goes into the tables that we print.
void  variables::printForTable() {
    printf("%8s %9s %9s %9s %9d\n", this->name.c_str(), this->type.c_str(), this->size.c_str(),
           this->scope.c_str(), this->memoryAddress);
}