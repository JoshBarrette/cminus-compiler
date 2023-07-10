/*
 * Main program for C- Compiler
 *
 * Written by: Stuart Hansen
 * Date: January 2018
 */

//
// Edited by Josh Barrette for CSCI 440 HW4
//

#include <iostream>
#include <string>
#include "common.h"
#include "treeParser.h"
#include "generator.h"

using namespace std;

extern int yyparse();

extern TreeNode * root;  // the root of the parse tree
extern FILE* yyin;

int main(int argc, char** argv) {
    // Set up the program to take the file to compile on the command line, if specified.
    if ( argc > 1 )
        yyin = fopen( argv[1], "r" );
    else {
        cout << "Reading from standard input." << endl;
        yyin = stdin;
    }

    // For the output file, we strip off the "cm" and add a "tm"
//    string outputFileName = string(argv[1]);
//    outputFileName = outputFileName.substr(0,outputFileName.length()-2) + "tm";

    yyparse();

    // Create the treeParser object and pass it root to parse
//    treeParser* treeParserObj = new treeParser(root);

    // Print the table
//    treeParserObj->printTable();

    string myName = "output.cm";
    generator* gen = new generator(root, argv[1]);
    gen->compileFile();

    return 0;
}


