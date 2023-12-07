#ifndef AST_H
#define AST_H

typedef enum { NODE_BOOL, NODE_NOT, NODE_BINOP } NodeType;
typedef enum { OP_AND, OP_OR } BinOpType;

typedef struct Node {
    NodeType type;
    union {
        int bool_val; // 1 for TRUE, 0 for FALSE
        struct {
            struct Node* expr;
        } not_expr; // Renamed from 'not' to 'not_expr'
        struct {
            struct Node* left;
            struct Node* right;
            BinOpType op; // OP_AND for AND, OP_OR for OR
        } binop;
    };
} Node;

Node* create_bool_node(int value);
Node* create_not_node(Node* expr);
Node* create_binop_node(Node* left, Node* right, BinOpType op);

#endif // AST_H