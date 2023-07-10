//
// Josh Barrette CSCI 440 HW4
//

#ifndef HW3FIX_TREEPARSER_H
#define HW3FIX_TREEPARSER_H

#include "TreeNode.h"
#include <vector>
#include <iostream>
#include <string>
#include "functions.h"
#include "variables.h"

class treeParser {
public:
    vector<functionsM*> funVec;
    vector<variables*> globVec;

    treeParser(TreeNode* root);

    void populateVectors(TreeNode* currentNode);
    void printTable();
    int nextGlobalAddress;
};


#endif
