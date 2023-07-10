/*
 * The implementation for our Tree Nodes
 *
 * Written by: Stuart Hansen
 * Date: January 2018
 */

#include <iostream>
#include <string>
#include "TreeNode.h"

using namespace std;

// Constructor that just takes a rule number
TreeNode::TreeNode (int ruleArg) {
    rule = ruleArg;
    text = string("");
}

// Constructor that takes a rule and some text
TreeNode::TreeNode (int ruleArg, char * textArg) {
    rule = ruleArg;
    text = textArg;
}

// Similar to the last constructor, but using a C++ string
TreeNode::TreeNode (int ruleArg, string stringArg) {
    rule = ruleArg;
    text = stringArg;
}

// Print the tree node with 0 indentation
void TreeNode::prefixPrint () {
    prefixPrint(0);
}

// Use indentation to illustrate parent child relationships
void TreeNode::prefixPrint (int indent) {
    for (int j=0; j<indent; j++) cout << " ";
    cout << this->rule << " " << this->text << " " << this->type << endl;
    int i;
    for (i=0; i<this->children.size(); i++) {
        this->children.at(i)->prefixPrint(indent+3);
    }
}
