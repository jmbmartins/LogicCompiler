#include <stdio.h>
#include "ast.h"
extern FILE* yyin;
extern int yyparse();
extern Node* parse_tree;
int evaluate(Node* node, SymbolTable* symbol_table);

// The interpret function takes a filename as an argument.
int interpret(const char* filename) {
    // Open the file for reading.
    FILE* fp = fopen(filename, "r");

    // If the file cannot be opened, print an error message and return -1.
    if (!fp) {
        perror(filename);
        return -1;
    }

    // Set yyin to the opened file and parse the file.
    yyin = fp;
    if (yyparse() != 0) {
        fprintf(stderr, "Parse error\n");
        return -1;
    }

    // Print the AST for debugging purposes.
    print_ast(parse_tree, 0);  // Print the AST

    fclose(fp);

    SymbolTable* symbol_table = create_symbol_table(); // Create a symbol table

    // Initialize the result to 0.
    int result = 0;  

    // If the parse_tree is a list of statements, evaluate each statement and update the result.
    if (parse_tree->type == NODE_STATEMENTS) {
        Node* current = parse_tree;
        while (current != NULL && current->statements.statement != NULL) {
            result = evaluate(current->statements.statement, symbol_table);  // Always update result
            current = current->statements.next;
        }
    // If the parse_tree is a single statement, evaluate the statement and update the result.
    } else {
        // If the parse_tree is a single statement
        result = evaluate(parse_tree, symbol_table);
    }

    // Free the memory allocated for the AST and the symbol table.
    free_node(parse_tree); 
    free_symbol_table(symbol_table); 

    // Return the result of the last expression evaluated.
    return result;  
}