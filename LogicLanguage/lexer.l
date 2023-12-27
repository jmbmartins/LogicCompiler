%option noyywrap
%option yylineno
%{
#include "ast.h"
#include "parser.h"
%}

%%

"AND"   { printf("Lexer: Identified token: AND\n"); return AND; }
"OR"    { printf("Lexer: Identified token: OR\n"); return OR; }
"NOT"   { printf("Lexer: Identified token: NOT\n"); return NOT; }
"TRUE"  { printf("Lexer: Identified token: TRUE\n"); return TRUE; }
"FALSE" { printf("Lexer: Identified token: FALSE\n"); return FALSE; }
"("     { printf("Lexer: Identified token: (\n"); return LPAREN; }
")"     { printf("Lexer: Identified token: )\n"); return RPAREN; }
";"     { printf("Lexer: Identified token: ;\n"); return SEMICOLON; }

"if"    { printf("Lexer: Identified token: if\n"); return IF; }
"else"  { printf("Lexer: Identified token: else\n"); return ELSE; }
"then"  { printf("Lexer: Identified token: then\n"); return THEN; }
"for"   { printf("Lexer: Identified token: for\n"); return FOR; }
"while" { printf("Lexer: Identified token: while\n"); return WHILE; }
"var"   { printf("Lexer: Identified token: var\n"); return VAR; }
"{"     { printf("Lexer: Identified token: {\n"); return LBRACE; }
"}"     { printf("Lexer: Identified token: }\n"); return RBRACE; }
"="     { printf("Lexer: Identified token: =\n"); return ASSIGN; }  
[a-zA-Z][a-zA-Z0-9]* { yylval.strval = strdup(yytext); printf("Lexer: Identified token: %s\n", yytext); return IDENTIFIER; }
[ \t\n] { /* ignore whitespace */ }
.       { fprintf(stderr, "Unrecognized character: %s\n", yytext); exit(1); }

%%