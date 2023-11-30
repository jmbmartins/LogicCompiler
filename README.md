# Project (40% - 8 Values)
Mandatory requirement: successfully compile/interpret the tests.

## Deliverables
### Deadline: 04/01/2023
- #01:Ast
- #02:Lexer
- #03:Parser
- #04:Compiler/Interpreter
- #05:Main
- #06:Makefile
- #07:Tests
- #08:Readme

------------------------------------------------------------------

## Sintax of My Language
<identifier> ::= <letter> { <letter> | <digit> | "_" }
<keyword> ::= "if" | "else" | "while" | "for" | "int" | "float" | ...
<data_type> ::= "int" | "float" | "char" | "bool"
<operator> ::= "+" | "-" | "*" | "/" | "%" | "==" | "!=" | "<" | ">" | "<=" | ">=" | "&&" | "||" | "!"
<expression> ::= <literal> | <identifier> | <binary_operation> | <unary_operation> | <function_call>
<statement> ::= <expression> ";" | <if_statement> | <while_loop> | <for_loop> | <function_definition>
<program> ::= { <statement> }

## Simple Compiler Project

### Overview
This project is a simple compiler for a custom language. It includes an interpreter for evaluating abstract syntax trees (ASTs). The compiler is designed to interpret basic arithmetic operations.

### Getting Started

#### Prerequisites
- GCC compiler

#### Building
To build the project, run the following command in the terminal:
```gcc -o interpreter interpreter.c```

### Running Tests
To run the tests, first build the test executable with the following command:
```gcc -o test test.c interpreter.c```


Then, run the tests with the following command:
```./test```


### Usage
The compiler interprets basic arithmetic operations. The language syntax is based on abstract syntax trees (ASTs). Each AST node represents a number or a binary operation. A binary operation node contains an operator ('+' for addition, '-' for subtraction) and two child nodes representing the operands.

Here's an example of how to create an AST for the expression "2 + 3":

```c
AstNode node1 = { .type = AST_NUMBER, .data = { .number = 2 } };
AstNode node2 = { .type = AST_NUMBER, .data = { .number = 3 } };
AstNode root = { .type = AST_BINARY_OPERATION, .data = { .binary_operation = { .op = '+', .left = &node1, .right = &node2 } } };
int result = interpret(&root);
```c
