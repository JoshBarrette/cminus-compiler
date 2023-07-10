/****************************************************/
/* File: CMinus.l                                   */
/* Lex specification for C- language from           */
/* Compiler Construction: Principles and Practice   */
/*                                                  */
/* This version is meant to work with lots of C++   */
/* code to make  functioning compiler.              */
/* Author: Stuart Hansen                            */
/* Date: January 2018                               */
/*                                                  */
/* To create Scanner.cpp                            */
/*   flex -oScanner.cpp CMinus.l                    */
/*                                                  */
/****************************************************/

%{

#include <stdio.h>
#include "common.h"
#include "Parser.hpp"


void skipcmnts(void);
void skipcmnts2(void);

/* lexeme of identifier or reserved word */
//char tokenString[101];

/* line number counter */
int lineno = 1;
%}

%option noyywrap

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%
"else"          {return ELSE;}
"if"            {return IF;}
"int"           {return INT;}
"return"        {return RETURN;}
"void"          {return VOID;}
"while"         {return WHILE;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"<"             {return LT;}
"<="            {return LE;}
">"             {return GT;}
">="            {return GE;}
"=="            {return EQ;}
"!="            {return NE;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"."             {return DOT;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACK;}
"]"             {return RBRACK;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}

{identifier}    {
                 yylval = new TreeNode(ID, string(yytext));
                 return ID;}
{number}        {
                 yylval = new TreeNode(NUM, string(yytext));
                 yylval->intvalue = atoi(yytext);
                 return NUM;}

{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"/*"            { skipcmnts(); }
.               {return ERROR;}


%%

/* function to skip C style comments
   borrowed mostly from:
   http://osr507doc.sco.com/en/tools/Lex_io.html
*/
void skipcmnts(void )
{
    for(;;)
    {
       char c = yyinput();
       if (c=='\n') lineno++;
       while (c != '*') {
          c = yyinput();
          if (c=='\n') lineno++;
       }
       c = yyinput();
       if (c == '\n') lineno++;
       if (c == '/') {
          return;
       }
       else {
          unput(yytext[yyleng-1]);
       }
    }
 }

/* Borrowed mostly from TINY.l */
void skipcmnts2 (void) {
   char previous = '\0';
   char c;
   c = yyinput();
   do
   {
      if (c == EOF) {
         break;
      }
      if (c == '\n') {
         lineno++;
      }
      previous = c;
      c = yyinput();
   } while (previous != '*' || c != '/');

}