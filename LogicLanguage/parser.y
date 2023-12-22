%{
#include <stdio.h>
#include "ast.h"
#include <stdlib.h>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

Node* parse_tree;
%}

%union {
    Node* node;
    int bool_val;
    BinOpType binop;
    char* strval;
}

%token <bool_val> TRUE FALSE
%token <binop> AND OR
%token IF THEN ELSE WHILE FOR VAR
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token <strval> IDENTIFIER
%token ASSIGN
%token NOT

%type <node> expr statement statements

%%

program:
    statements { parse_tree = $1; }
;

statement:
    IF LPAREN expr RPAREN THEN LBRACE statement RBRACE ELSE LBRACE statement RBRACE { $$ = create_if_node($3, $7, $11); }
    | WHILE LPAREN expr RPAREN LBRACE statement RBRACE { $$ = create_while_node($3, $6); }
    | FOR LPAREN statement SEMICOLON expr SEMICOLON statement RPAREN LBRACE statement RBRACE { $$ = create_for_node($3, $5, $7, $10); }
    | VAR IDENTIFIER ASSIGN expr SEMICOLON { $$ = create_var_node($2, $4); }
;

statements:
    statement { $$ = $1; }
    | statements statement { $$ = append_statement($1, $2); }
;

expr:
    TRUE { $$ = create_bool_node(1); }
    | FALSE { $$ = create_bool_node(0); }
    | NOT expr { $$ = create_not_node($2); }
    | expr AND expr { $$ = create_binop_node($1, $3, OP_AND); }
    | expr OR expr { $$ = create_binop_node($1, $3, OP_OR); }
    | IDENTIFIER { $$ = create_identifier_node($1); }
;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}