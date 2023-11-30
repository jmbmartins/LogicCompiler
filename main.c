#include <stdio.h>
#include "ast.h"
#include "interpreter.h"

int main() {
    // Create an AST for the expression "2 + 3"
    AstNode node1 = { .type = AST_NUMBER, .data = { .number = 2 } };
    AstNode node2 = { .type = AST_NUMBER, .data = { .number = 3 } };
    AstNode root = { .type = AST_BINARY_OPERATION, .data = { .binary_operation = { .op = '+', .left = &node1, .right = &node2 } } };

    // Interpret the AST
    int result = interpret(&root);

    // Print the result
    printf("Result: %d\n", result);

    return 0;
}