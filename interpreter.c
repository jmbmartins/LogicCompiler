#include <stdio.h>
#include "interpreter.h"


int interpret(AstNode* node) {
  switch (node->type) {
    case AST_NUMBER:
      return node->data.number;
    case AST_BINARY_OPERATION:
      int left = interpret(node->data.binary_operation.left);
      int right = interpret(node->data.binary_operation.right);
      switch (node->data.binary_operation.op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        // Add other operators here...
        default:
          fprintf(stderr, "error: unknown operator '%c'\n", node->data.binary_operation.op);
          return 0;
      }
    default:
      fprintf(stderr, "error: unknown node type %d\n", node->type);
      return 0;
  }
}
