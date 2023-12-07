%option noyywrap
%{
#include "ast.h"
#include "parser.h"
%}

%%

"AND"   { return AND; }
"OR"    { return OR; }
"NOT"   { return NOT; }
"TRUE"  { yylval.bool_val = 1; return BOOL; }
"FALSE" { yylval.bool_val = 0; return BOOL; }
"("     { return LPAREN; }
")"     { return RPAREN; }
[ \t\n] { /* ignore whitespace */ }
.       { fprintf(stderr, "Unrecognized character: %s\n", yytext); exit(1); }

%%