#include <stdio.h>
#include "ast.h"
extern FILE* yyin;
extern int yyparse();
extern Node* parse_tree;
int evaluate(Node* node, SymbolTable* symbol_table); // Declare evaluate

int interpret(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return -1;
    }

    yyin = fp;
    if (yyparse() != 0) {
        fprintf(stderr, "Parse error\n");
        return -1;
    }

    print_ast(parse_tree, 0);  // Print the AST

    fclose(fp);

    SymbolTable* symbol_table = create_symbol_table(); // Create a symbol table

    int result = 0;  // Initialize result to 0

    // If the parse_tree is a list of statements
    if (parse_tree->type == NODE_STATEMENTS) {
        Node* current = parse_tree;
        while (current != NULL && current->statements.statement != NULL) {
            result = evaluate(current->statements.statement, symbol_table);  // Always update result
            current = current->statements.next;
        }
    } else {
        // If the parse_tree is a single statement
        result = evaluate(parse_tree, symbol_table);
    }

    free_node(parse_tree); // Free the parsed AST
    free_symbol_table(symbol_table); // Free the symbol table

    return result;  // Return the result of the last expression evaluated
}