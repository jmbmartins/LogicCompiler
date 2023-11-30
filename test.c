// test.c
#include <stdio.h>
#include "ast.h"
#include "interpreter.h"

void test(char* name, AstNode* node, int expected) {
  int result = interpret(node);
  if (result == expected) {
    printf("%s: PASS\n", name);
  } else {
    printf("%s: FAIL (expected %d, got %d)\n", name, expected, result);
  }
}

int main() {
  // Test 1: 2 + 3
  AstNode test1 = { .type = AST_BINARY_OPERATION, .data.binary_operation = { .op = '+', .left = &(AstNode){ .type = AST_NUMBER, .data.number = 2 }, .right = &(AstNode){ .type = AST_NUMBER, .data.number = 3 } } };
  test("2 + 3", &test1, 5);

  // Test 2: 7 - 4
  AstNode test2 = { .type = AST_BINARY_OPERATION, .data.binary_operation = { .op = '-', .left = &(AstNode){ .type = AST_NUMBER, .data.number = 7 }, .right = &(AstNode){ .type = AST_NUMBER, .data.number = 4 } } };
  test("7 - 4", &test2, 3);

  // Add more tests here...

  return 0;
}