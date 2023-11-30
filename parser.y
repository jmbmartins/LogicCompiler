%{
#include <stdio.h>
%}

%token NUMBER
%token IDENTIFIER
%token IF
%token ELSE
%token WHILE
%token FOR
%token INT
%token FLOAT
%token CHAR
%token BOOL
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token MODULO
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_THAN_EQUAL
%token GREATER_THAN_EQUAL
%token AND
%token OR
%token NOT
%token SEMICOLON
%token EOL

%%

program:
  line
  | program line
  ;

line:
  '\n'
  | statement '\n'
  ;

statement:
  expression SEMICOLON
  ;

expression:
  NUMBER
  | IDENTIFIER
  | expression PLUS expression { $$ = $1 + $3; }
  | expression MINUS expression { $$ = $1 - $3; }
  | expression MULTIPLY expression { $$ = $1 * $3; }
  | expression DIVIDE expression { $$ = $1 / $3; }
  | expression MODULO expression { $$ = $1 % $3; }
  | expression EQUAL expression { $$ = $1 == $3; }
  | expression NOT_EQUAL expression { $$ = $1 != $3; }
  | expression LESS_THAN expression { $$ = $1 < $3; }
  | expression GREATER_THAN expression { $$ = $1 > $3; }
  | expression LESS_THAN_EQUAL expression { $$ = $1 <= $3; }
  | expression GREATER_THAN_EQUAL expression { $$ = $1 >= $3; }
  | expression AND expression { $$ = $1 && $3; }
  | expression OR expression { $$ = $1 || $3; }
  | NOT expression { $$ = !$2; }
  ;

%%

int main() {
  yyparse();
  return 0;
}

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}