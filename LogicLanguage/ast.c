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

Symbol* lookup_symbol(SymbolTable* symbol_table, char* name) {
    Symbol* symbol = symbol_table->head;
    while (symbol != NULL) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    printf("Symbol not found: %s\n", name);  // Add this line
    return NULL;
}

Symbol* create_symbol(char* name, int value) {
    Symbol* symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->value = value;
    symbol->next = NULL;
    printf("Created symbol: %s = %d\n", name, value);  // Add this line
    return symbol;
}

void add_symbol(SymbolTable* symbol_table, Symbol* symbol) {
    symbol->next = symbol_table->head;
    symbol_table->head = symbol;
    printf("Added symbol: %s = %d\n", symbol->name, symbol->value);  // Add this line
}

SymbolTable* create_symbol_table() {
    SymbolTable* symbol_table = malloc(sizeof(SymbolTable));
    if (symbol_table == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    symbol_table->head = NULL;
    return symbol_table;
}

void free_symbol_table(SymbolTable* symbol_table) {
    Symbol* symbol = symbol_table->head;
    while (symbol != NULL) {
        Symbol* next_symbol = symbol->next;
        free(symbol->name);  // Assuming name was dynamically allocated
        free(symbol);
        symbol = next_symbol;
    }
    free(symbol_table);
}

Node* create_assign_node(char* name, Node* value) {
    printf("Creating assign node: %s = ", name);
    print_ast(value, 0);  // Assuming print_ast is a function that prints an AST
    Node* node = malloc(sizeof(Node));
    node->type = NODE_ASSIGN;
    node->assign.name = strdup(name);  // Make a dynamically allocated copy of name
    node->assign.value = value;
    return node;
}

int evaluate(Node* node, SymbolTable* symbol_table) {
    printf("Evaluating node of type: %d\n", node->type);
    print_ast(node, 0);
    switch (node->type) {
        case NODE_BOOL:
            printf("Bool value: %d\n", node->bool_val);
            return node->bool_val;
        case NODE_NOT:
            return !evaluate(node->not_expr.expr, symbol_table); 
        case NODE_BINOP:
            int left_val = evaluate(node->binop.left, symbol_table);
            int right_val = evaluate(node->binop.right, symbol_table);
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
            if (evaluate(node->if_expr.cond, symbol_table)) {
                return evaluate(node->if_expr.then_branch, symbol_table);
            } else {
                return evaluate(node->if_expr.else_branch, symbol_table);
            }
        case NODE_WHILE:
            while (evaluate(node->while_loop.cond, symbol_table)) {
                evaluate(node->while_loop.body, symbol_table);
            }
            return 0; // While loops do not return a value
        case NODE_FOR:
            for (evaluate(node->for_loop.init, symbol_table); evaluate(node->for_loop.cond, symbol_table); evaluate(node->for_loop.increment, symbol_table)) {
                evaluate(node->for_loop.body, symbol_table);
            }
            return 0; // For loops do not return a value
        case NODE_VAR: {
            int value = evaluate(node->var_decl.value, symbol_table);
            Symbol* symbol = lookup_symbol(symbol_table, node->var_decl.name);
            if (symbol == NULL) {
                symbol = create_symbol(node->var_decl.name, value);
                add_symbol(symbol_table, symbol);
            } else {
                symbol->value = value;
            }
            printf("Assigned variable: %s = %d\n", node->var_decl.name, value);
            return value;
        }
        case NODE_IDENTIFIER: {
            Symbol* symbol = lookup_symbol(symbol_table, node->identifier);
            if (symbol == NULL) {
                fprintf(stderr, "Undefined variable: %s\n", node->identifier);
                exit(1);
            }
            printf("Retrieved variable: %s = %d\n", node->identifier, symbol->value);
            return symbol->value;
        }
        case NODE_ASSIGN: {
            int value = evaluate(node->assign.value, symbol_table);
            printf("Evaluator: Evaluated assign node: %s = %d\n", node->assign.name, value);
            Symbol* symbol = lookup_symbol(symbol_table, node->assign.name);
            if (symbol == NULL) {
                printf("Error: Attempted to assign to undeclared variable: %s\n", node->assign.name);
                exit(1);
            }
            symbol->value = value;
            printf("Assigned variable: %s = %d\n", node->assign.name, value);
            return value;
        }
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
        case NODE_ASSIGN:
            free(node->assign.name); // Assuming name was dynamically allocated
            free_node(node->assign.value);
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
    printf("ENTER IN THIS FUNCTION APPEND");
    // printf("Appending statement of type: %d\n", statement->type);
    if (statement == NULL) {
        printf("Error: statement is NULL\n");
        return statements;
    }
    if (statements == NULL) {
        printf("Error: statements is NULL\n");
        return create_statements_node(statement, NULL);
    }
    Node* current = statements;
    while (current->statements.next != NULL) {
        current = current->statements.next;
    }
    current->statements.next = create_statements_node(statement, NULL);
    return statements;
}

void print_ast(Node* node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    switch (node->type) {
        case NODE_BOOL:
            printf("NODE_BOOL: %d\n", node->bool_val);
            break;
        case NODE_NOT:
            printf("NODE_NOT\n");
            print_ast(node->not_expr.expr, depth + 1);
            break;
        case NODE_BINOP:
            printf("NODE_BINOP: %d\n", node->binop.op);
            print_ast(node->binop.left, depth + 1);
            print_ast(node->binop.right, depth + 1);
            break;
        case NODE_IF:
            printf("NODE_IF\n");
            print_ast(node->if_expr.cond, depth + 1);
            print_ast(node->if_expr.then_branch, depth + 1);
            print_ast(node->if_expr.else_branch, depth + 1);
            break;
        case NODE_WHILE:
            printf("NODE_WHILE\n");
            print_ast(node->while_loop.cond, depth + 1);
            print_ast(node->while_loop.body, depth + 1);
            break;
        case NODE_FOR:
            printf("NODE_FOR\n");
            print_ast(node->for_loop.init, depth + 1);
            print_ast(node->for_loop.cond, depth + 1);
            print_ast(node->for_loop.increment, depth + 1);
            print_ast(node->for_loop.body, depth + 1);
            break;
        case NODE_VAR:
            printf("NODE_VAR: %s\n", node->var_decl.name);
            print_ast(node->var_decl.value, depth + 1);
            break;
        case NODE_IDENTIFIER:
            printf("NODE_IDENTIFIER: %s\n", node->identifier);
            break;
        case NODE_STATEMENTS:
            printf("NODE_STATEMENTS\n");
            print_ast(node->statements.statement, depth + 1);
            if (node->statements.next != NULL) {
                print_ast(node->statements.next, depth);
            }
            break;
        case NODE_ASSIGN:
            printf("NODE_ASSIGN: %s\n", node->assign.name);
            print_ast(node->assign.value, depth + 1);
            break;
        // Add cases for other node types...
        default:
            printf("Unknown node type: %d\n", node->type);
            break;
    }
}

