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
";"     { return SEMICOLON; }
"="     { return EQUALS; }

"if"    { return IF; }
"else"  { return ELSE; }
"then"  { return THEN; }
"for"   { return FOR; }
"while" { return WHILE; }
"do"    { return DO; }
"var"   { return VAR; }
"let"   { return LET; }
"const" { return CONST; }

[a-zA-Z][a-zA-Z0-9]* {
    yylval.identifier = strdup(yytext);
    return IDENTIFIER;
}

[ \t\n] { /* ignore whitespace */ }
.       { fprintf(stderr, "Unrecognized character: %s\n", yytext); exit(1); }

%%