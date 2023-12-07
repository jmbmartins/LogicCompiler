%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
extern int yylex();
void yyerror(const char *s);
extern FILE* yyin;
Node* parse_tree; // Declare parse_tree
%}

%union {
    Node* node;
    int bool_val;
}

%token <bool_val> BOOL
%token AND OR NOT
%token LPAREN RPAREN

%type <node> expr

%%

expr:
    BOOL { $$ = create_bool_node($1); parse_tree = $$; }
    | NOT expr { $$ = create_not_node($2); parse_tree = $$; }
    | expr AND expr { $$ = create_binop_node($1, $3, OP_AND); parse_tree = $$; }
    | expr OR expr { $$ = create_binop_node($1, $3, OP_OR); parse_tree = $$; }
    | LPAREN expr RPAREN { $$ = $2; parse_tree = $$; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

Node* parse(FILE* fp) {
    yyin = fp;
    if (yyparse() == 0) {
        return parse_tree;
    } else {
        return NULL;
    }
}