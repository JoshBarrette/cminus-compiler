/*
 * Declarations for the Tree Node class
 *
 * Written by: Stuart Hansen
 * Date: January 2018
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <vector>

using namespace std;

class TreeNode {
public:
    int rule;       // grammar rule -- See CMinus.y
    string type;    // used for variables, parameters and functions
    string text;    // text associated with this node, e.g. variable name, function name
    int intvalue;   // if there is a numeric value, it is stored here.

    // Vector of all the children of this node
    vector<TreeNode*> children;

    // A variety of constructors
    TreeNode (int ruleArg);
    TreeNode (int ruleArg, char* textArg);
    TreeNode (int ruleArg, string stringArg);

    // Print this node with 0 prefix
    void prefixPrint ();

    // Print this node with the specified prefix
    void prefixPrint (int indent);
};


#endif
