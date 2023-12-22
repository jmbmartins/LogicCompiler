#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>  // Add this line

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

Node* create_if_node(Node* cond, Node* then_branch, Node* else_branch) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_IF;
    node->if_expr.cond = cond;
    node->if_expr.then_branch = then_branch;
    node->if_expr.else_branch = else_branch;
    return node;
}

Node* create_while_node(Node* cond, Node* body) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_WHILE;
    node->while_loop.cond = cond;
    node->while_loop.body = body;
    return node;
}

Node* create_for_node(Node* init, Node* cond, Node* increment, Node* body) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_FOR;
    node->for_loop.init = init;
    node->for_loop.cond = cond;
    node->for_loop.increment = increment;
    node->for_loop.body = body;
    return node;
}

Node* create_var_node(char* name, Node* value) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_VAR;
    node->var_decl.name = strdup(name);  // Make a dynamically allocated copy of name
    node->var_decl.value = value;
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
        case NODE_IF:
            if (evaluate(node->if_expr.cond)) {
                return evaluate(node->if_expr.then_branch);
            } else {
                return evaluate(node->if_expr.else_branch);
            }
        case NODE_WHILE:
            while (evaluate(node->while_loop.cond)) {
                evaluate(node->while_loop.body);
            }
            return 0; // While loops do not return a value
        case NODE_FOR:
            for (evaluate(node->for_loop.init); evaluate(node->for_loop.cond); evaluate(node->for_loop.increment)) {
                evaluate(node->for_loop.body);
            }
            return 0; // For loops do not return a value
        case NODE_VAR:
            // You will need to implement variable storage and lookup
            // This is a placeholder implementation
            return evaluate(node->var_decl.value);
        default:
            fprintf(stderr, "Invalid node type\n");
            return 0;
    }
}

void free_node(Node* node) {
    if (node == NULL) {
        return;
    }

    // Free child nodes
    switch (node->type) {
        case NODE_NOT:
            free_node(node->not_expr.expr);
            break;
        case NODE_BINOP:
            free_node(node->binop.left);
            free_node(node->binop.right);
            break;
        case NODE_IF:
            free_node(node->if_expr.cond);
            free_node(node->if_expr.then_branch);
            free_node(node->if_expr.else_branch);
            break;
        case NODE_WHILE:
            free_node(node->while_loop.cond);
            free_node(node->while_loop.body);
            break;
        case NODE_FOR:
            free_node(node->for_loop.init);
            free_node(node->for_loop.cond);
            free_node(node->for_loop.increment);
            free_node(node->for_loop.body);
            break;
        case NODE_VAR:
            free(node->var_decl.name); // Assuming name was dynamically allocated
            free_node(node->var_decl.value);
            break;
        case NODE_IDENTIFIER: // Add this case
            free(node->identifier);
            break;
        default:
            break;
    }

    // Free the node itself
    free(node);
}

Node* create_identifier_node(char* identifier) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = NODE_IDENTIFIER;
    new_node->identifier = strdup(identifier);
    return new_node;
}

Node* create_statements_node(Node* statement, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = NODE_STATEMENTS;
    new_node->statements.statement = statement;
    new_node->statements.next = next;
    return new_node;
}

Node* append_statement(Node* statements, Node* statement) {
    if (statements == NULL) {
        return create_statements_node(statement, NULL);
    }
    Node* current = statements;
    while (current->statements.next != NULL) {
        current = current->statements.next;
    }
    current->statements.next = create_statements_node(statement, NULL);
    return statements;
}

