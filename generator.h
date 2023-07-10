#ifndef HW5_GENERATOR_H
#define HW5_GENERATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include "treeParser.h"
#include "TreeNode.h"

using namespace std;

class generator {
public:
    generator(TreeNode* root, string fileName);
    void closeFile();

    void writeCom(string comment);
    void writeRO(int lineNum, string opCode, int targetReg, int inputReg1, int inputReg2);
    void writeRM(int lineNum, string opCode, int targetReg, int inputReg, int immediate);
    void halt();
    void push(int regToPush);
    void pop(int regToPopInto);
    void fillRegisterForOperation(TreeNode* node, int reg);
    void doOp(TreeNode* node);

    bool isGlobal(TreeNode* node);
    bool isParam(TreeNode* node);
    bool isLocal(TreeNode* node);
    void fillOffsets(TreeNode* node);

    void compileFile();
    void preamble();
    void findRules(TreeNode* currentNode);

    void assignment(TreeNode* currentNode);
    void operations(TreeNode* currentNode);
    void output(TreeNode* currentNode);

    string getNotInequality(TreeNode* node);
    void prepareForComparison(TreeNode* node);
    void ifElse(TreeNode* node);
    void ifThen(TreeNode* node);
    void whileLoop(TreeNode* node);

    treeParser* tree;
    TreeNode* root;

    // Needs to be this type for ->substr() to work.
    basic_string<char> fileName;
    ofstream outputFile;

    // The register number if given counters
    int stackPtr = 4;
    int globalPtr = 6;
    int framePtr = 5;

    // Line counter
    int ln = 0;

    // Used when pulling variable data from memory
    int from;
    int offset;
};


#endif //HW5_GENERATOR_H
