%{
#include "y.tab.h"
%}

%%

[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yylval = strdup(yytext); return IDENTIFIER; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"for" { return FOR; }
"int" { return INT; }
"float" { return FLOAT; }
"char" { return CHAR; }
"bool" { return BOOL; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
"%" { return MODULO; }
"==" { return EQUAL; }
"!=" { return NOT_EQUAL; }
"<" { return LESS_THAN; }
">" { return GREATER_THAN; }
"<=" { return LESS_THAN_EQUAL; }
">=" { return GREATER_THAN_EQUAL; }
"&&" { return AND; }
"||" { return OR; }
"!" { return NOT; }
";" { return SEMICOLON; }
\n { return EOL; }
. { return yytext[0]; }

%%