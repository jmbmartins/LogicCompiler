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
# Programming Language of Operators (Only)
1. **Tokens:** Your language will have the following tokens:
   - `AND`: Represents the logical AND operator.
   - `OR`: Represents the logical OR operator.
   - `NOT`: Represents the logical NOT operator.
   - `TRUE`: Represents the boolean value true.
   - `FALSE`: Represents the boolean value false.
   - `(` and `)`: Parentheses for grouping expressions.

2. **Grammar:** The grammar of your language could be defined as follows:
   - `expression`: An expression can be a `boolean`, a `not_expression`, or a `binary_expression`.
   - `boolean`: A boolean can be either `TRUE` or `FALSE`.
   - `not_expression`: A not_expression is `NOT` followed by an `expression`.
   - `binary_expression`: A binary_expression is an `expression` followed by a `binary_operator` followed by another `expression`. The `binary_operator` can be either `AND` or `OR`.
   - Parentheses can be used to change the precedence of the operators.
  
Backus-Naur Form (BNF):   
```
<expression> ::= <boolean>
               | <not_expression>
               | <binary_expression>
               | "(" <expression> ")"

<boolean> ::= "TRUE"
            | "FALSE"

<not_expression> ::= "NOT" <expression>

<binary_expression> ::= <expression> <binary_operator> <expression>

<binary_operator> ::= "AND"
                    | "OR"
```

## Sintax
<identifier> ::= <letter> { <letter> | <digit> | "_" }
<keyword> ::= "if" | "else" | "while" | "for" | "int" | "float" | ...
<data_type> ::= "int" | "float" | "char" | "bool"
<operator> ::= "+" | "-" | "*" | "/" | "%" | "==" | "!=" | "<" | ">" | "<=" | ">=" | "&&" | "||" | "!"
<expression> ::= <literal> | <identifier> | <binary_operation> | <unary_operation> | <function_call>
<statement> ::= <expression> ";" | <if_statement> | <while_loop> | <for_loop> | <function_definition>
<program> ::= { <statement> }

# Compiler Project for Programming Language of Operators (Only)

## Overview
This project is a simple compiler for a custom language. It includes an interpreter for evaluating abstract syntax trees (ASTs). The compiler is designed to interpret basic arithmetic operations.

## Getting Started
## 01: Ast
The abstract syntax tree (AST) is defined in `ast.h`. Each node in the AST represents a number or a binary operation.

## 02: Lexer
The lexer is responsible for breaking down the input into tokens. This part of the project is still under development.

## 03: Parser
The parser takes the tokens produced by the lexer and constructs an AST. This part of the project is still under development.

## 04: Compiler/Interpreter
The interpreter is defined in `interpreter.c` and `interpreter.h`. It takes an AST and evaluates it to produce a result.

## 05: Main
The main function is located in `main.c`. It runs a series of tests on the interpreter.

## 06: Makefile
The Makefile for this project is still under development.

## 07: Tests
The tests are defined in `test.c`. They test the functionality of the interpreter by creating ASTs and checking that they are evaluated correctly.

### Prerequisites
- GCC compiler

### Building
To build the project, run the following command in the terminal:
```gcc -o interpreter interpreter.c```

## Running Tests
To run the tests, first build the test executable with the following command:
```gcc -o test test.c interpreter.c```


Then, run the tests with the following command:
```./test```


## Usage
The compiler interprets basic arithmetic operations. The language syntax is based on abstract syntax trees (ASTs). Each AST node represents a number or a binary operation. A binary operation node contains an operator ('+' for addition, '-' for subtraction) and two child nodes representing the operands.

Here's an example of how to create an AST for the expression "2 + 3":

```c
AstNode node1 = { .type = AST_NUMBER, .data = { .number = 2 } };
AstNode node2 = { .type = AST_NUMBER, .data = { .number = 3 } };
AstNode root = { .type = AST_BINARY_OPERATION, .data = { .binary_operation = { .op = '+', .left = &node1, .right = &node2 } } };
int result = interpret(&root);
```c
