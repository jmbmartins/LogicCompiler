%option noyywrap
%{
#include "ast.h"
#include "parser.h"
%}

%%

"AND"   { return AND; }
"OR"    { return OR; }
"NOT"   { return NOT; }
"TRUE"  { return TRUE; }
"FALSE" { return FALSE; }
"("     { return LPAREN; }
")"     { return RPAREN; }
";"     { return SEMICOLON; }

"if"    { return IF; }
"else"  { return ELSE; }
"then"  { return THEN; }
"for"   { return FOR; }
"while" { return WHILE; }
"var"   { return VAR; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"="     { return ASSIGN; printf("Lexer: Identified token: =\n"); }
[a-zA-Z][a-zA-Z0-9]* { yylval.strval = strdup(yytext); printf("Lexer: Identified token: %s\n", yytext); return IDENTIFIER; }
[ \t\n] { /* ignore whitespace */ }
.       { fprintf(stderr, "Unrecognized character: %s\n", yytext); exit(1); }

%%