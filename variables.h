//
// Josh Barrette CSCI 440 HW4
//

#ifndef HW3FIX_VARIABLES_H
#define HW3FIX_VARIABLES_H

#include <string>
#include "TreeNode.h"

using namespace std;

class variables {
public:
    string name;
    string type;
    string size;
    string scope;
    int memoryAddress;
    string description;

    variables(TreeNode* node, string scope);
    void printForTable();
};


#endif
