/*
 * This file contains declarations that are common to both the Flex and Bison files
 *
 * Written by: Stuart Hansen
 * Date: January 2018
 */
#ifndef COMMONH
#define COMMONH
#include "TreeNode.h"

// We define the type of object created by the parse,
// In this case, a pointer to a tree node
#define YYSTYPE TreeNode*
#endif
