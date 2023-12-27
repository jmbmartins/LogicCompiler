%{
#include <stdio.h>
#include "ast.h"
#include <stdlib.h>
#include "lex.yy.h"  // Include the Flex header
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

Node* parse_tree;

void print_ast(Node* node, int depth);  // Declare print_ast

Node* create_assign_node(char* name, Node* value);  // Declare create_assign_node
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

%type <node> expr statement statements init_expr

%%

program:
    statements { parse_tree = $1; printf("Parser: Parsed program\n"); }
;

init_expr:
    VAR IDENTIFIER ASSIGN expr { $$ = create_var_node($2, $4); printf("Parser: Parsed variable declaration\n"); }
    | IDENTIFIER ASSIGN expr { $$ = create_assign_node($1, $3); printf("Parser: Created assign node: %s = expr\n", $1); }
    | expr { $$ = $1; }
;

statement:
    IF LPAREN expr RPAREN THEN LBRACE statement RBRACE ELSE LBRACE statement RBRACE SEMICOLON { $$ = create_if_node($3, $7, $11); printf("Parser: Parsed if-else statement\n"); }
    | WHILE LPAREN expr RPAREN LBRACE statement RBRACE SEMICOLON { $$ = create_while_node($3, $6); printf("Parser: Parsed while statement\n"); }
    | FOR LPAREN init_expr SEMICOLON expr SEMICOLON init_expr RPAREN LBRACE statement RBRACE SEMICOLON { $$ = create_for_node($3, $5, $7, $10); printf("Parser: Parsed for statement\n"); }
    | VAR IDENTIFIER ASSIGN expr SEMICOLON { $$ = create_var_node($2, $4); printf("Parser: Parsed variable declaration\n"); }
    | IDENTIFIER ASSIGN expr SEMICOLON { $$ = create_assign_node($1, $3); printf("Parser: Created assign node: %s = expr\n", $1); print_ast($$, 0); }
    | error SEMICOLON { fprintf(stderr, "Syntax error at line %d\n", yylineno); yyerrok; }
;

statements:
    statement { $$ = create_statements_node($1, NULL); printf("Parser: Parsed single statement\n"); print_ast($$, 0); }  
    | statements statement { $$ = append_statement($1, $2); printf("Parser: Parsed multiple statements\n"); print_ast($$, 0); }  
;

expr:
    TRUE { $$ = create_bool_node(1); printf("Parser: Parsed TRUE\n"); }
    | FALSE { $$ = create_bool_node(0); printf("Parser: Parsed FALSE\n"); }
    | NOT expr { $$ = create_not_node($2); printf("Parser: Parsed NOT expression\n"); }
    | expr AND expr { $$ = create_binop_node($1, $3, OP_AND); printf("Parser: Parsed AND expression\n"); }
    | expr OR expr { $$ = create_binop_node($1, $3, OP_OR); printf("Parser: Parsed OR expression\n"); }
    | IDENTIFIER { $$ = create_identifier_node($1); printf("Parser: Parsed identifier: %s\n", $1); }
;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    if (yychar < 256) {
        fprintf(stderr, "Unexpected token: %c\n", yychar);
    } else {
        fprintf(stderr, "Unexpected token number: %d\n", yychar);
    }
    exit(1);
}