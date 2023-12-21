// tests.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  // Add this line
#include "ast.h"

void test_create_bool_node() {
    Node* node = create_bool_node(1);
    assert(node->type == NODE_BOOL);
    assert(node->bool_val == 1);
    free_node(node);
}

void test_create_not_node() {
    Node* expr = create_bool_node(1);
    Node* node = create_not_node(expr);
    assert(node->type == NODE_NOT);
    assert(node->not_expr.expr == expr);
    free_node(node);
}

void test_create_binop_node() {
    Node* left = create_bool_node(1);
    Node* right = create_bool_node(0);
    Node* node = create_binop_node(left, right, OP_AND);
    assert(node->type == NODE_BINOP);
    assert(node->binop.left == left);
    assert(node->binop.right == right);
    assert(node->binop.op == OP_AND);
    free_node(node);
}

void test_create_var_node() {
    char* name = strdup("test");  // Dynamically allocate name
    Node* value = create_bool_node(1);
    Node* node = create_var_node(name, value);
    assert(node->type == NODE_VAR);
    assert(strcmp(node->var_decl.name, "test") == 0);
    assert(node->var_decl.value == value);
    free_node(node);
    free(name);  // Free name after the node is freed
}

void test_create_identifier_node() {
    Node* node = create_identifier_node("x");
    assert(node->type == NODE_IDENTIFIER);
    assert(strcmp(node->identifier, "x") == 0);
    free_node(node);
}

void test_evaluate() {
    Node* left = create_bool_node(1);
    Node* right = create_bool_node(0);
    Node* node = create_binop_node(left, right, OP_AND);
    assert(evaluate(node) == 0);
    free_node(node);
}

int main() {
    test_create_bool_node();
    test_create_not_node();
    test_create_binop_node();
    test_create_var_node();
    test_create_identifier_node();
    test_evaluate();
    printf("All tests passed!\n");
    return 0;
}