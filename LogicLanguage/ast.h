#ifndef AST_H
#define AST_H

typedef enum { NODE_BOOL, NODE_NOT, NODE_BINOP, NODE_IF, NODE_WHILE, NODE_FOR, NODE_VAR, NODE_IDENTIFIER, NODE_ASSIGN, NODE_STATEMENTS } NodeType;  // Add NODE_ASSIGN
typedef enum { OP_AND, OP_OR } BinOpType;

typedef struct Symbol {
    char* name;
    int value;
    struct Symbol* next;
} Symbol;

typedef struct SymbolTable {
    Symbol* head;
} SymbolTable;

typedef struct {
    char* name;
    struct Node* value;
} Assign;

typedef struct Node {
    NodeType type;
    union {
        int bool_val;
        struct {
            struct Node* expr;
        } not_expr;
        struct {
            struct Node* left;
            struct Node* right;
            BinOpType op;
        } binop;
        struct {
            struct Node* cond;
            struct Node* then_branch;
            struct Node* else_branch;
        } if_expr;
        struct {
            struct Node* cond;
            struct Node* body;
        } while_loop;
        struct {
            struct Node* init;
            struct Node* cond;
            struct Node* increment;
            struct Node* body;
        } for_loop;
        struct {
            char* name;
            struct Node* value;
        } var_decl;
        struct {
            struct Node* statement;
            struct Node* next;
        } statements;
        char* identifier;
        Assign assign;  // Add Assign assign
    };
} Node;

Node* create_bool_node(int value);
Node* create_not_node(Node* expr);
Node* create_binop_node(Node* left, Node* right, BinOpType op);
Node* create_if_node(Node* cond, Node* then_branch, Node* else_branch);
Node* create_while_node(Node* cond, Node* body);
Node* create_for_node(Node* init, Node* cond, Node* increment, Node* body);
Node* create_var_node(char* name, Node* value);
Node* create_identifier_node(char* identifier);
Node* create_statements_node(Node* statement, Node* next);
Node* append_statement(Node* statements, Node* statement);
void free_node(Node* node);
int evaluate(Node* node, SymbolTable* symbol_table);
Symbol* lookup_symbol(SymbolTable* symbol_table, char* name);
Symbol* create_symbol(char* name, int value);
void add_symbol(SymbolTable* symbol_table, Symbol* symbol);

// Added function declarations
SymbolTable* create_symbol_table();
void free_symbol_table(SymbolTable* symbol_table);
void print_ast(Node* node, int depth);

#endif // AST_H