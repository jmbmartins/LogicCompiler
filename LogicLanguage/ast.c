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
    node->var_decl.name = name;
    node->var_decl.value = value;
    printf("Created var node with name: %s and value: %p\n", name, value);  // Print out the node
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
    Node* node = malloc(sizeof(Node));
    node->type = NODE_ASSIGN;
    node->assign.name = strdup(name);  // Make a dynamically allocated copy of name
    node->assign.value = value;
    // Print the name and value
    printf("Created assign node with name: %s and value: ", name);
    print_ast(value, 0);
    return node;
}

int interpret_assign_node(Node* node, SymbolTable* symbol_table) {
    // Evaluate the right-hand side of the assignment
    int value = evaluate(node->assign.value, symbol_table);

    // Check if the symbol already exists in the symbol table
    Symbol* symbol = lookup_symbol(symbol_table, node->assign.name);
    if (symbol == NULL) {
        // If the symbol does not exist, create and add it
        symbol = create_symbol(node->assign.name, value);
        add_symbol(symbol_table, symbol);
    } else {
        // If the symbol already exists, update its value
        symbol->value = value;
    }

    printf("Assigned variable: %s = %d\n", node->assign.name, value);

    // Return the value that was assigned
    return value;
}

int evaluate(Node* node, SymbolTable* symbol_table) {
    printf("Evaluating node of type: %d\n", node->type);
    print_ast(node, 0);
    switch (node->type) {
        case NODE_BOOL:
            printf("Bool value: %d\n", node->bool_val);
            return node->bool_val;
        case NODE_NOT:
            int not_val = !evaluate(node->not_expr.expr, symbol_table);
            printf("NOT value: %d\n", not_val);
            return not_val;
        case NODE_BINOP:
            int left_val = evaluate(node->binop.left, symbol_table);
            int right_val = evaluate(node->binop.right, symbol_table);
            printf("Left value: %d, Right value: %d\n", left_val, right_val);
            switch (node->binop.op) {
                case OP_AND:
                    int and_val = left_val && right_val;
                    printf("AND value: %d\n", and_val);
                    return and_val;
                case OP_OR:
                    int or_val = left_val || right_val;
                    printf("OR value: %d\n", or_val);
                    return or_val;
                default:
                    fprintf(stderr, "Invalid binary operator\n");
                    return 0;
            }
        case NODE_IF:
            int cond_if = evaluate(node->if_expr.cond, symbol_table);
            printf("IF condition: %d\n", cond_if);
            if (cond_if) {
                return evaluate(node->if_expr.then_branch, symbol_table);
            } else {
                return evaluate(node->if_expr.else_branch, symbol_table);
            }
        case NODE_WHILE:
            while (evaluate(node->while_loop.cond, symbol_table)) {
                evaluate(node->while_loop.body, symbol_table);
            }
            printf("Finished WHILE loop\n");
            return 0; // While loops do not return a value
        case NODE_FOR:
            for (evaluate(node->for_loop.init, symbol_table); evaluate(node->for_loop.cond, symbol_table); evaluate(node->for_loop.increment, symbol_table)) {
                evaluate(node->for_loop.body, symbol_table);
            }
            printf("Finished FOR loop\n");
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
            int value = interpret_assign_node(node, symbol_table);
            printf("Assignment value: %d\n", value);
            return value; // return the value from the assignment
            break;
        }
        case NODE_STATEMENTS:
            Node* current = node;
            while (current != NULL) {
                evaluate(current->statements.statement, symbol_table);
                current = current->statements.next;
            }
            return 0; // Statements do not return a value
            break;
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
    Node* node = malloc(sizeof(Node));
    node->type = NODE_STATEMENTS;
    node->statements.statement = statement;

    // Check if next statement already exists in the list
    Node* check = next;
    while (check != NULL) {
        if (check == statement) {
            printf("Statement already exists in the list. Not appending.\n");
            node->statements.next = next;
            return node;
        }
        if (check->type == NODE_STATEMENTS) {
            check = check->statements.next;
        } else {
            break;
        }
    }

    node->statements.next = next;
    return node;
}

Node* append_statement(Node* statements, Node* statement) {
    printf("Appending statement of type: %d\n", statement->type);
    printf("Statement: %p\n", statement);  // Print out the statement
    if (statement == NULL) {
        printf("Error: statement is NULL\n");
        return statements;
    }
    if (statements == NULL) {
        printf("Error: statements is NULL\n");
        return create_statements_node(statement, NULL);
    }

    // Check if statement already exists in the list
    Node* check = statements;
    while (check != NULL) {
        if (check == statement) {
            printf("Statement already exists in the list. Not appending.\n");
            return statements;
        }
        if (check->type == NODE_STATEMENTS) {
            check = check->statements.next;
        } else {
            break;
        }
    }

    // Append statement to the list
    Node* current = statements;
    while (current->statements.next != NULL) {
        current = current->statements.next;
    }
    current->statements.next = create_statements_node(statement, NULL);
    printf("Appended statement of type: %d\n", statement->type);

    // Print the statements list
    printf("Statements list after appending:\n");
    current = statements;
    while (current != NULL) {
        printf("Statement of type: %d\n", current->type);
        if (current->type == NODE_STATEMENTS) {
            current = current->statements.next;
        } else {
            break;
        }
    }

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

