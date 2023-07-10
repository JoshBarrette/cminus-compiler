//
// Josh Barrette CSCI 440 HW4
//

#ifndef HW3FIX_FUNCTIONS_H
#define HW3FIX_FUNCTIONS_H

#include <vector>
#include "variables.h"
#include <string>
#include "TreeNode.h"

// Had to rename this to functionsM because c++ didn't like functions
class functionsM {
public:
    vector<variables*> paramsVec;
    vector<variables*> localsVec;
    string functionName;
    string returnType;
    int memoryAddress;

    functionsM(TreeNode* root);

    void populateVectors(TreeNode* node);
    void printTable();
};

#endif
