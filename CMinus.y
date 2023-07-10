/****************************************************/
/* File: CMinus.y                                   */
/* The CMinus Bison specification file              */
/* Grammar from: Compiler Construction: Principles  */
/* and Practice.                                    */
/*                                                  */
/* Version for use in entire compiler.              */
/*                                                  */
/* To compile to C++ (both .cpp and .hpp):           */
/* bison -oParser.cpp -d CMinus.y                   */
/*    Note that the grammar has one shift/reduce    */
/*    conflict. The if-then-else                    */
/*                                                  */
/* Stuart Hansen                                    */
/* January 2018                                     */
/****************************************************/
%{
#include <iostream>
#include <string>
#include "TreeNode.h"
#include "common.h"

using namespace std;

TreeNode * root;
//string id;

int yylex();
int yyerror(string message);

//extern char* yytext;
extern int lineno;
%}



/* book-keeping tokens */
%token   ENDFILE ERROR

/* reserved words */
%token    ELSE IF INT RETURN VOID WHILE

/* special symbols */
%token    PLUS MINUS TIMES OVER LT LE GT GE EQ NE ASSIGN
%token    SEMI COMMA DOT LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

/* Comment tokens, currently not used */
%token    LCOMMENT RCOMMENT

/* multicharacter tokens */
%token    ID NUM

%% /* Grammar for CMinus */
/* Rule 10 */
program     : declaration_list   {root = $1;}

            ;

/* Rule 20 */
declaration_list    : declaration_list declaration  { $$ = $1;
                                                      $$->children.push_back($2);
                                                    }

/* Rule 21 */
            | declaration    { $$ = new TreeNode(21, string("decl list"));
                               $$->children.push_back($1);
                             }
            ;

/* Rule 30 */
declaration : var_declaration  {$$ = $1;}  /* We skip having a separate declaration node */

/* Rule 31 */
            | fun_declaration  {$$ = $1;}  /* We again skip having a separate declaration node */
            ;

/* Rule 40 */
var_declaration : type_specifier ID SEMI {$$ = new TreeNode (40, string("var decl"));
                                                                  $$->children.push_back($1);
                                                                  $$->children.push_back($2);}

/* Rule 41 */
            | type_specifier ID  LBRACK NUM RBRACK SEMI {$$ = new TreeNode (41, string("array decl"));
                                                                                $$->children.push_back($1);
                                                                                $$->children.push_back($2);
                                                                                $$->children.push_back($4);}
            ;

/* Rule 50 */
type_specifier  : INT       {$$ = new TreeNode(50, string("int"));}

/* Rule 51 */
                | VOID      {$$ = new TreeNode(51, string("void"));}
            ;

/* Rule 60 */
fun_declaration    : type_specifier ID LPAREN params RPAREN compound_stmt
                      { $$ = new TreeNode (60, $2->text);
                        $$->type = $1->text;     /* type_specifier's text is functions type */
                        $$->children.push_back($4);
                        $$->children.push_back($6);
                      }
            ;

/* Rule 70 */
params      : param_list    {$$ = $1;}
            ;

/* Rule 71 */
            | VOID          {$$ = $1;}
            ;

/* Rule 80 */
param_list  : param_list COMMA param {$$ = $1;
                                      $$->children.push_back($3); }
            ;

/* Rule 81 */
            | param                 {$$ = new TreeNode (81, string("param"));
                                     $$->children.push_back($1); }
            ;

/* Rule 90 */
param       : type_specifier ID  {$$ = new TreeNode (90, $2->text);
                                  $$->type = $1->text; }
            ;

/* Rule 91 */
            | type_specifier ID LBRACK RBRACK {$$ = new TreeNode (91, $2->text);
                                               $$->type = $1->text+"[]"; }
            ;

/* Rule 100 */
compound_stmt   : LBRACE local_declarations statement_list RBRACE
                         { $$ = new TreeNode (100, string("compound statement"));
                           $$->children.push_back($2);
                           $$->children.push_back($3);
                         }
            ;

/* Rule 110 */
local_declarations  : local_declarations var_declaration
                        { $$ = $1;
                          $$->children.push_back($2);
                        }

/* Rule 111 */
                    | { $$ = new TreeNode(111, string("local decl"));
                      }
            ;


/* Rule 120 */
statement_list  : statement_list statement
                        { $$ = $1;
                          $$->children.push_back($2);
                        }

/* Rule 121 */
                | { $$ = new TreeNode(121, string("expression list"));
                  }
            ;

/* Rule 130 */
statement   : expression_stmt {$$ = $1;}

/* Rule 131 */
            | compound_stmt {$$ = $1;}

/* Rule 132 */
            | selection_stmt {$$ = $1;}

/* Rule 133 */
            | iteration_stmt {$$ = $1;}

/* Rule 144 */
            | return_stmt {$$ = $1;}
            ;

/* Rule 140 */
expression_stmt : expression SEMI   {$$ = $1; }

/* Rule 141 */
                | SEMI  {$$ = new TreeNode (141, string("empty expression")); }
            ;

/* Rule 150 */
selection_stmt  : IF LPAREN expression RPAREN statement
                        { $$ = new TreeNode (150, string("if..then"));
                          $$->children.push_back($3);
                          $$->children.push_back($5);
                        }

/* Rule 151 */
                | IF LPAREN expression RPAREN statement ELSE statement
                        { $$ = new TreeNode (151, string("if..else"));
                          $$->children.push_back($3);
                          $$->children.push_back($5);
                          $$->children.push_back($7);
                        }
            ;

/* Rule 160 */
iteration_stmt  : WHILE LPAREN expression RPAREN statement
                        { $$ = new TreeNode (160, string("while"));
                          $$-> children.push_back($3);
                          $$-> children.push_back($5);
                        }
            ;

/* Rule 170 */
return_stmt : RETURN SEMI           { $$ = new TreeNode(170, string("empty return"));}

/* Rule 171 */
            | RETURN expression SEMI { $$ = new TreeNode (171, string("return with value"));
                                       $$->children.push_back($2);}

/* Rule 180 */
expression  : var ASSIGN expression  { $$ = new TreeNode (180, string("assignment"));
                                       $$->children.push_back($1);
                                       $$->children.push_back($3);
                                     }

/* Rule 181 */
            | simple_expression      { $$ = $1;}

            ;

/* Rule 190 */
var         : ID    { $$ = $1; $$->rule=190; }

/* Rule 191 */
            | ID LBRACK expression RBRACK   { $$ = new TreeNode(191, $1->text);
                                              $$->children.push_back($3);
                                            }
            ;

/* Rule 200 */
simple_expression   : additive_expression relop additive_expression
                                    { $$ = new TreeNode (200, string("relop"));
                                      $$->children.push_back($2);
                                      $$->children.push_back($1);
                                      $$->children.push_back($3);
                                    }

/* Rule 201 */
                    | additive_expression { $$ = $1; }
            ;

/* Rule 210 */
relop       : LE  {$$ = new TreeNode (210, string("<="));}

/* Rule 211 */
            | LT  {$$ = new TreeNode (211, string("<")); }

/* Rule 212 */
            | GT  {$$ = new TreeNode (212, string(">"));}

/* Rule 213 */
            | GE  {$$ = new TreeNode (213, string(">="));}

/* Rule 214 */
            | EQ  {$$ = new TreeNode (214, string("=="));}

/* Rule 215 */
            | NE  {$$ = new TreeNode (215, string("!="));}
            ;

/* Rule 220 */
additive_expression : additive_expression addop term
                     {
                      $$ = $2;
                      $$->rule = 220;
                      $$->children.push_back($1);
                      $$->children.push_back($3);
                     }

/* Rule 221 */
            | term    {$$ = $1; }

            ;

/* Rule 230 */
addop       : PLUS  {$$ = new TreeNode (230, string("+"));}

/* Rule 231 */
            | MINUS  {$$ = new TreeNode (231, string("-"));}
            ;

/* Rule 240 */
term        : term mulop factor
                   { $$ = $2;
                     $$->rule = 240;
                     $$->children.push_back($1);
                     $$->children.push_back($3);
                    }

/* Rule 241 */
            | factor  { $$ = $1; }
            ;

/* Rule 250 */
mulop       : TIMES  {$$ = new TreeNode (250, string("*"));}

/* Rule 251 */
            | OVER   {$$ = new TreeNode (251, string("/"));}
            ;

/* Rule 260 */
factor      : LPAREN expression RPAREN   {$$ = $2; /*$$rule->260;*/ } /* I think we want to know the type of expression */

/* Rule 261 */
            | var   { $$ = $1; $$->rule = 261;}

/* Rule 262 */
            | call {$$ = $1; $$->rule = 262;}

/* Rule 263 */
            | NUM   {$$ = $1; $$->rule=263;}
            ;

/* Rule 270 */
call        : ID LPAREN args RPAREN
                    { $$ = new TreeNode (270, $1->text);
                      $$->children.push_back($3);
                    }
            ;

/* Rule 280 */
args        : arg_list   {$$ = $1; }

/* Rule 281 */
            |  { $$ = new TreeNode(281, string("args")); }
            ;

/* Rule 290 */
arg_list    : arg_list COMMA expression
               { $$ = $1;
                 $$->children.push_back($3);
               }

/* Rule 291 */
            | expression
                { $$ = new TreeNode (291, string("arg list"));
                  $$->children.push_back($1);
                }
            ;


%%

/*
  Dumbed down version of yyerror, mostly borrowed from TINY.y
*/
int yyerror(string message)
{
  cout << "Syntax error at line " << lineno << " " << message << endl;
  return 0;
}


