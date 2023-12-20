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
    char* identifier;
}

%token <bool_val> BOOL
%token AND OR NOT
%token IF ELSE THEN FOR WHILE DO VAR LET CONST
%token <identifier> IDENTIFIER
%token LPAREN RPAREN SEMICOLON EQUALS

%type <node> expr statement var_declaration

%%

expr:
    BOOL { $$ = create_bool_node($1); parse_tree = $$; }
    | NOT expr { $$ = create_not_node($2); parse_tree = $$; }
    | expr AND expr { $$ = create_binop_node($1, $3, OP_AND); parse_tree = $$; }
    | expr OR expr { $$ = create_binop_node($1, $3, OP_OR); parse_tree = $$; }
    | LPAREN expr RPAREN { $$ = $2; parse_tree = $$; }
    ;

statement:
    IF LPAREN expr RPAREN THEN statement ELSE statement { $$ = create_if_node($3, $6, $8); parse_tree = $$; }
    | WHILE LPAREN expr RPAREN DO statement { $$ = create_while_node($3, $6); parse_tree = $$; }
    | FOR LPAREN var_declaration SEMICOLON expr SEMICOLON expr RPAREN DO statement { $$ = create_for_node($3, $5, $7, $10); parse_tree = $$; }
    | var_declaration { $$ = $1; parse_tree = $$; }
    ;

var_declaration:
    VAR IDENTIFIER EQUALS expr { $$ = create_var_node($2, $4); parse_tree = $$; }
    | LET IDENTIFIER EQUALS expr { $$ = create_var_node($2, $4); parse_tree = $$; }
    | CONST IDENTIFIER EQUALS expr { $$ = create_var_node($2, $4); parse_tree = $$; }
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