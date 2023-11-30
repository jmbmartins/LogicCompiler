#ifndef AST_H
#define AST_H

typedef enum { AST_NUMBER, AST_BINARY_OPERATION } AstNodeType;

typedef struct AstNode {
  AstNodeType type;
  union {
    int number;
    struct {
      char op;
      struct AstNode* left;
      struct AstNode* right;
    } binary_operation;
  } data;
} AstNode;

#endif /* AST_H */