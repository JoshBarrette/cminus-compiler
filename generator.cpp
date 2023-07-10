#include "generator.h"
#include <iostream>
#include "TreeNode.h"
#include "treeParser.h"

using namespace std;

#include <string>

generator::generator(TreeNode* root, string fileName) {
    this->root = root;
    this->tree = new treeParser(root);

    // We need the "../" so that it writes to the right file
    this-> fileName = "../" + fileName.substr(0,fileName.length()-2) + "tm";

//    tree->printTable();
//    this->root->prefixPrint();
    this->outputFile.open(this->fileName, ios::out);
}

void generator::closeFile() {
    this->outputFile.close();
}

void generator::writeCom(string comment) {
    this->outputFile << "*\t" << comment << endl;
}

// targetReg = inputReg1 OP inputReg2
void generator::writeRO(int lineNum, string opCode, int targetReg, int inputReg1, int inputReg2) {
    this->outputFile << lineNum << ":\t" << opCode << " " << targetReg << "," << inputReg1 << "," << inputReg2 << endl;
}

// targetReg = offset ( inputReg )
void generator::writeRM(int lineNum, string opCode, int targetReg, int offset, int inputReg) {
    this->outputFile << lineNum << ":\t" << opCode << " " << targetReg << "," << offset << "(" << inputReg << ")" << endl;
}

// Prints the halt command for the end of the program
void generator::halt() {
    this->writeCom("\n*\tHalt");
    this->writeRO(ln++, "HALT", 0, 0, 0);
}

// Pushes a given register onto the stack and increments the stack pointer
void generator::push(int regToPush) {
    this->writeCom("Push to stack");
    writeRM(ln++, "ST", regToPush, 0, this->stackPtr);
    writeRM(ln++, "LDC", 0, 1, 0);
    writeRO(ln++, "SUB", this->stackPtr, this->stackPtr, 0);
}

// Pops the stack into the given register and decrements the stack pointer
void generator::pop(int regToPopInto) {
    this->writeCom("Pop from stack");
    writeRM(ln++, "LDC", 0, 1, 0);
    writeRO(ln++, "ADD", this->stackPtr, this->stackPtr, 0);
    writeRM(ln++, "LD", regToPopInto, 0, this->stackPtr);
}

// Checks to see if the given register is a global variable
bool generator::isGlobal(TreeNode* node){
    for (variables* i : this->tree->globVec) {
        if (i->name == node->text) {
            this->from = this->globalPtr;
            this->offset = i->memoryAddress;
            return true;
        }
    }
    return false;
}

// Checks to see if the given register is a parameter
bool generator::isParam(TreeNode* node){
    for (functionsM* i : this->tree->funVec) {
        for (variables* j : i->paramsVec)
            if (j->name == node->text) {
                this->from = this->framePtr;
                this->offset = i->memoryAddress;
                return true;
            }
    }
    return false;
}

// Checks to see if the given register is a local variable
bool generator::isLocal(TreeNode* node){
    for (functionsM* i : this->tree->funVec) {
        for (variables* j : i->localsVec)
            if (j->name == node->text) {
                this->from = this->stackPtr;
                this->offset = i->memoryAddress;
                return true;
            }
    }
    return false;
}

// Fills the from and offset variable with the correct data for getting a variables data into a register
void generator::fillOffsets(TreeNode* node) {
    // This all feels super overcomplicated, but I don't see a better way
    if (isGlobal(node)){
        return;
    } else if (isParam(node)){
        return;
    } else {
        isLocal(node);
    }
}

// Compiles the file with the preamble, the body, and the halt command
void generator::compileFile() {
    this->preamble();
    this->findRules(this->root);
    this->halt();
    this->closeFile();
}

// Adds our preamble to the beginning of the file
void generator::preamble() {
    this->writeCom("Preamble");
    this->writeRM(ln++, "LD", this->globalPtr, 0, 0 );
    this->writeRM(ln++, "LDC", 0, this->tree->globVec.size(), 0 );
    this->writeRO(ln++, "SUB", this->framePtr, 6, 0);
    this->writeRO(ln++, "SUB", this->stackPtr, 6, 0);
    this->writeRM(ln++, "LDC", 0, 0, 0 );
}

// This is the method that will go through the tree in DFS manner to check for rules and fill in the body of the tm file
void generator::findRules(TreeNode* currentNode) {
    if (currentNode->rule == 180) {
        this->assignment(currentNode);
    } else if (currentNode->rule == 262) {
        this->output(currentNode);
    } else if(currentNode->rule == 151) {
        this->ifElse(currentNode);
    } else if (currentNode->rule == 150) {
        this->ifThen(currentNode);
    } else if (currentNode->rule == 160) {
        this->whileLoop(currentNode);
    } else {
        for (int i = 0; i < currentNode->children.size(); i++) {
            this->findRules(currentNode->children.at(i));
        }
    }
}

// Handles assignment of variables
void generator::assignment(TreeNode* currentNode) {
    this->writeCom("\n*\tAssignment");
    int rule = currentNode->children.at(1)->rule;
    if (rule == 262) {
        this->writeCom("Input");
        fillOffsets(currentNode->children.at(0));
        writeRO(ln++, "IN", 0, 0, 0);
        writeRM(ln++, "ST", 0, 0-this->offset,this->from);
    } else if (rule == 220 || rule == 240) {
        operations(currentNode);
        this->pop(0);
        fillOffsets(currentNode->children.at(0));
        writeRM(ln++, "ST", 0, 0-this->offset,this->from);
    } else if (rule == 263) {
        fillOffsets(currentNode->children.at(0));
        writeRM(ln++, "LDC", 0, stoi(currentNode->children.at(1)->text), 0);
        writeRM(ln++, "ST", 0, 0-this->offset,this->from);
    }
}

// Recursive function that handles expressions
void generator::operations(TreeNode* currentNode) {
    int rule1 = currentNode->children.at(0)->rule;
    int rule2 = currentNode->children.at(1)->rule;
    if ((rule1 == 240 || rule1 == 220) && (rule2 == 240 || rule2 == 220)) {
        operations(currentNode->children.at(0));
        operations(currentNode->children.at(1));
        this->pop(0);
        this->pop(1);
        this->doOp(currentNode);
        this->push(0);
    } else if (rule1 == 240 || rule1 == 220) {
        operations(currentNode->children.at(0));
        this->pop(0);
        this->fillRegisterForOperation(currentNode->children.at(1), 1);
        this->doOp(currentNode);
        this->push(0);
    } else if (rule2 == 240 || rule2 == 220) {
        operations(currentNode->children.at(1));
        this->pop(0);
        this->fillRegisterForOperation(currentNode->children.at(0), 1);
        this->doOp(currentNode);
        this->push(0);
    } else {
        this->fillRegisterForOperation(currentNode->children.at(0), 0);
        this->fillRegisterForOperation(currentNode->children.at(1), 1);
        this->doOp(currentNode);
        this->push(0);
    }
}

// Fills a given register with either a constant or a variable's data depending on the rule
void generator::fillRegisterForOperation(TreeNode* node, int reg) {
    if (node->rule == 261) {
        fillOffsets(node);
        writeRM(ln++, "LD", reg, 0-this->offset,this->from);
    } else if (node->rule == 263) {
        writeRM(ln++, "LDC", reg, stoi(node->text), 0);
    }
}

// Adds the actual operation to the tm file
void generator::doOp(TreeNode* node) {
    this->writeCom("Doing an Operation");
    if (node->text == "+") {
        writeRO(ln++, "ADD", 0, 0, 1);
    } else if (node->text == "-") {
        writeRO(ln++, "SUB", 0, 0, 1);
    } else if (node->text == "*") {
        writeRO(ln++, "MUL", 0, 0, 1);
    } else if (node->text == "/") {
        writeRO(ln++, "DIV", 0, 0, 1);
    }
}

// Handles output commands
void generator::output(TreeNode* currentNode) {
    this->writeCom("\n*\tOutput");
    for (TreeNode* i : currentNode->children.at(0)->children) {
        if (i->rule == 261) {
            fillOffsets(i);
            writeRM(ln++, "LD", 0, 0-this->offset,this->from);
            writeRO(ln++, "OUT", 0, 0, 0);
        } else if (i->rule == 263) {
            writeRM(ln++, "LDC", 0, stoi(i->text), 0);
            writeRO(ln++, "OUT", 0, 0, 0);
        } else if (i->rule == 220 || i->rule == 240) {
            operations(i);
            this->pop(0);
            fillOffsets(i->children.at(0));
            writeRO(ln++, "OUT", 0, 0, 0);
        } else if (i->rule == 262) {
            writeRO(ln++, "IN", 0, 0, 0);
            writeRO(ln++, "OUT", 0, 0, 0);
        }
    }
}

// Decides which command to use based on the inequality symbol
string generator::getNotInequality(TreeNode* node) {
    if (node->text == ">") {
        return "JLE";
    } else if (node->text == ">=") {
        return "JLT";
    } else if (node->text == "<") {
        return "JGE";
    } else if (node->text == "<=") {
        return "JGT";
    } else if (node->text == "==") {
        return "JNE";
    } else {
        return "JEQ";
    }
}

// Fills registers with the data they need to make a comparison
void generator::prepareForComparison(TreeNode* node) {
    if (node->children.at(1)-> rule == 220 || node->children.at(1)-> rule == 240) {
        operations(node->children.at(1));
    } else {
        fillRegisterForOperation(node->children.at(1), 0);
        push(0);
    }

    if (node->children.at(2)-> rule == 220 || node->children.at(2)-> rule == 240) {
        operations(node->children.at(2));
    } else {
        fillRegisterForOperation(node->children.at(2), 1);
        push(1);
    }

    pop(1);
    pop(0);
}

// Handles if else commands
void generator::ifElse(TreeNode* node) {
    TreeNode* relop = node->children.at(0);

    writeCom("\n*\tifElse");
    int elseLine;
    prepareForComparison(relop);
    writeRO(ln++, "SUB", 0, 0, 1);
    int jumpLine = ln++;

    this->findRules(node->children.at(1));
    int endIfLine = ln++;

    elseLine = ln;
    this->findRules(node->children.at(2));
    writeRM(endIfLine, "LDC", 7, ln,0);

    writeCom("ifElse Jumps");
    writeRM(jumpLine, getNotInequality(relop->children.at(0)), 0, elseLine - jumpLine, 7);
}

// Handles if then commands
void generator::ifThen(TreeNode* node) {
    TreeNode* relop = node->children.at(0);

    writeCom("\n*\tifThen");
    prepareForComparison(relop);
    writeRO(ln++, "SUB", 0, 0, 1);
    int jumpLine = ln++;

    this->findRules(node->children.at(1));

    writeCom("ifThen Jump");
    writeRM(jumpLine, getNotInequality(relop->children.at(0)), 0, ln - jumpLine - 1, 7);
}

// Handles while loops
void generator::whileLoop(TreeNode* node) {
    TreeNode* relop = node->children.at(0);

    writeCom("\n*\twhileLoop");
    prepareForComparison(relop);

    writeRO(ln++, "SUB", 0, 0, 1);
    int jumpLine = ln++;

    this->findRules(node->children.at(1));

    prepareForComparison(relop);
    writeRO(ln++, "SUB", 0, 0, 1);
    writeCom("While loop jump");
    writeRM(ln++, "LDC", 7, jumpLine,0);

    writeRM(jumpLine, getNotInequality(relop->children.at(0)), 0, ln, 7);
}
