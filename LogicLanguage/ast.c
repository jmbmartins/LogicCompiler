#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <string.h>  

// Creates a boolean node with the given boolean value
Node* create_bool_node(int bool_val) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_BOOL;
    node->bool_val = bool_val;
    return node;
}

// Creates a NOT node with the given expression
Node* create_not_node(Node* expr) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_NOT;
    node->not_expr.expr = expr; // The expression to negate
    return node;
}

// Creates a binary operation node with the given left and right expressions and operation type
Node* create_binop_node(Node* left, Node* right, BinOpType op) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_BINOP;
    node->binop.left = left; // The left operand
    node->binop.right = right; // The right operand
    node->binop.op = op; // The operation to perform
    return node;
}

// Creates an IF node with the given condition, then branch, and else branch
Node* create_if_node(Node* cond, Node* then_branch, Node* else_branch) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_IF;
    node->if_expr.cond = cond; // The condition to check
    node->if_expr.then_branch = then_branch; // The branch to execute if the condition is true
    node->if_expr.else_branch = else_branch; // The branch to execute if the condition is false
    return node;
}

// Creates a WHILE node with the given condition and body
Node* create_while_node(Node* cond, Node* body) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_WHILE;
    node->while_loop.cond = cond; // The condition to check
    node->while_loop.body = body; // The body to execute while the condition is true
    return node;
}

// Creates a FOR node with the given initialization, condition, increment, and body
Node* create_for_node(Node* init, Node* cond, Node* increment, Node* body) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_FOR;
    node->for_loop.init = init; // The initialization statement
    node->for_loop.cond = cond; // The condition to check
    node->for_loop.increment = increment; // The increment statement
    node->for_loop.body = body; // The body to execute while the condition is true
    return node;
}

// Creates a variable declaration node with the given name and value
Node* create_var_node(char* name, Node* value) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_VAR;
    node->var_decl.name = name; // The name of the variable
    node->var_decl.value = value; // The value of the variable
    printf("Created var node with name: %s and value: %p\n", name, value);  // Print out the node
    return node;
}

// Looks up a symbol in the given symbol table by its name
Symbol* lookup_symbol(SymbolTable* symbol_table, char* name) {
    Symbol* symbol = symbol_table->head;
    while (symbol != NULL) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    printf("Symbol not found: %s\n", name);  // Print out if the symbol is not found
    return NULL;
}

// Creates a symbol with the given name and value
Symbol* create_symbol(char* name, int value) {
    Symbol* symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name); // The name of the symbol
    symbol->value = value; // The value of the symbol
    symbol->next = NULL;
    printf("Created symbol: %s = %d\n", name, value);  // Print out the created symbol
    return symbol;
}

// Adds a symbol to the given symbol table
void add_symbol(SymbolTable* symbol_table, Symbol* symbol) {
    symbol->next = symbol_table->head;
    symbol_table->head = symbol;
    printf("Added symbol: %s = %d\n", symbol->name, symbol->value);  // Print out the added symbol
}

// Creates a symbol table
SymbolTable* create_symbol_table() {
    SymbolTable* symbol_table = malloc(sizeof(SymbolTable));
    if (symbol_table == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    symbol_table->head = NULL;
    return symbol_table;
}

// Frees the memory allocated for the given symbol table. 
void free_symbol_table(SymbolTable* symbol_table) {
    Symbol* symbol = symbol_table->head;
    while (symbol != NULL) {
        Symbol* next_symbol = symbol->next;
        free(symbol->name);  
        free(symbol);
        symbol = next_symbol;
    }
    free(symbol_table);
}

// Creates an assignment node with a given name and value. 
Node* create_assign_node(char* name, Node* value) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_ASSIGN;
    node->assign.name = strdup(name);  // Make a dynamically allocated copy of name
    node->assign.value = value;
    printf("Created assign node with name: %s and value: ", name);
    print_ast(value, 0);
    return node;
}

// Evaluates the value of an assignment node and either creates a new symbol with that value or updates the value of an existing symbol in the symbol table.
int interpret_assign_node(Node* node, SymbolTable* symbol_table) {
    int value = evaluate(node->assign.value, symbol_table);

    Symbol* symbol = lookup_symbol(symbol_table, node->assign.name);
    if (symbol == NULL) {
        symbol = create_symbol(node->assign.name, value);
        add_symbol(symbol_table, symbol);
    } else {
        symbol->value = value;
    }

    printf("Assigned variable: %s = %d\n", node->assign.name, value);

    // Return the value that was assigned
    return value;
}

// Evaluates a node based on its type. It handles all node types, including boolean, not, binary operation, if, while, for, variable, identifier, assignment, and statements nodes.
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

// Frees a node and all its child nodes.
void free_node(Node* node) {
    if (node == NULL) {
        return;
    }

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
            free(node->var_decl.name); 
            free_node(node->var_decl.value);
            break;
        case NODE_IDENTIFIER: 
            free(node->identifier);
            break;
        case NODE_ASSIGN:
            free(node->assign.name);
            free_node(node->assign.value);
            break;
        default:
            break;
    }

    free(node);
}


// Creates an identifier node with the given identifier.
Node* create_identifier_node(char* identifier) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = NODE_IDENTIFIER;
    new_node->identifier = strdup(identifier);
    return new_node;
}

// Creates a statements node with the given statement and next node.
Node* create_statements_node(Node* statement, Node* next) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_STATEMENTS;
    node->statements.statement = statement;

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

// Appends a statement to the list of statements.
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

    Node* current = statements;
    while (current->statements.next != NULL) {
        current = current->statements.next;
    }
    current->statements.next = create_statements_node(statement, NULL);
    printf("Appended statement of type: %d\n", statement->type);

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

// Prints the Abstract Syntax Tree (AST) starting from the given node.
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
        default:
            printf("Unknown node type: %d\n", node->type);
            break;
    }
}

