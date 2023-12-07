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
# Logic Compiler
This project is a simple logic compiler that evaluates logical expressions involving `AND`, `OR`, and `NOT` operations on boolean values `TRUE` and `FALSE`.

## **Tokens:** The language have the following tokens:
   - `AND`: Logical AND operation
   - `OR`: Logical OR operation
   - `NOT`: Logical NOT operation
   - `TRUE`: Boolean value true
   - `FALSE`: Boolean value false
   - `(`: Left parenthesis
   - `)`: Right parenthesis

3. **Grammar:** Language Grammar could be defined as follows:
  - `expr`: An expression, which can be a boolean value, a `NOT` expression, or a binary operation (`AND` or `OR`). Expressions can also be grouped using parentheses.

  
Backus-Naur Form (BNF):   
```
<expr> ::= <BOOL>
         | NOT <expr>
         | <expr> AND <expr>
         | <expr> OR <expr>
         | ( <expr> )
```

Where:
- `<BOOL>` is a boolean value (`TRUE` or `FALSE`).
- `NOT <expr>` is a `NOT` operation on an expression.
- `<expr> AND <expr>` is an `AND` operation between two expressions.
- `<expr> OR <expr>` is an `OR` operation between two expressions.
- `( <expr> )` is an expression grouped by parentheses.

## Files

- `ast.c` and `ast.h`: Define the abstract syntax tree (AST) for the logical expressions.
- `interpreter.c` and `interpreter.h`: Define the interpreter that evaluates the AST.
- `lexer.l`: Defines the lexical analyzer that tokenizes the input.
- `parser.y`: Defines the syntax analyzer that parses the tokens into an AST.
- `main.c`: Contains the main function that ties everything together.
- `Makefile`: Defines the build rules for the project.
- `test.c`: Contains a test program that runs the logic compiler on several test files and checks if the output matches the expected result.


## Building and Running
The project uses a Makefile for building the executable. Here's how you can build and run the project:

1. To build the project, navigate to the project directory in your terminal and run the following command:
```bash
make
```
This command will compile the source files and generate an executable named logic_compiler.


2. To run the logic compiler on a file, use the following command:
```bash
./logic_compiler <file>
```


3. To clean the project (remove the compiled files), use the following command:
```bash
make clean
```
This command will remove the object files and the logic_compiler executable.


4. To run the tests, first compile the test program with the following command:
```bash
gcc test.c -o test
```
Then, run the test program with the following command:
```bash
./test
```
This will print the output of each test file and whether the test passed or failed.

## Usage

To use the logic compiler, write a logical expression in a text file using the tokens and grammar defined above. Then, run the logic compiler on the file using the command shown in the "Building and Running" section. The logic compiler will print the result of the expression.

Here's an example:

1. Write your logical expression in a text file. For example, you might write the following in a file named `example.txt`:
```text
NOT (TRUE AND FALSE) OR TRUE
```

2. Run the logic compiler on the file:

```bash
./logic_compiler example.txt
```

Output:
The logic compiler will print the result of the expression:
```text
TRUE
```


