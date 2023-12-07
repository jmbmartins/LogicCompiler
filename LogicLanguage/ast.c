#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

Node* create_bool_node(int bool_val) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_BOOL;
    node->bool_val = bool_val;
    return node;
}

Node* create_not_node(Node* expr) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_NOT;
    node->not_expr.expr = expr; // Updated from 'not' to 'not_expr'
    return node;
}

Node* create_binop_node(Node* left, Node* right, BinOpType op) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_BINOP;
    node->binop.left = left;
    node->binop.right = right;
    node->binop.op = op;
    return node;
}

int evaluate(Node* node) {
    switch (node->type) {
        case NODE_BOOL:
            return node->bool_val;
        case NODE_NOT:
            return !evaluate(node->not_expr.expr); 
        case NODE_BINOP:
            int left_val = evaluate(node->binop.left);
            int right_val = evaluate(node->binop.right);
            switch (node->binop.op) {
                case OP_AND:
                    return left_val && right_val;
                case OP_OR:
                    return left_val || right_val;
                default:
                    fprintf(stderr, "Invalid binary operator\n");
                    return 0;
            }
        default:
            fprintf(stderr, "Invalid node type\n");
            return 0;
    }
}