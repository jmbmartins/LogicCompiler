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
This is a simple logic compiler that interprets a language with boolean expressions and control flow structures.

## **Tokens:** The language have the following tokens:

- Keywords: `AND`, `OR`, `NOT`, `TRUE`, `FALSE`, `if`, `else`, `then`, `for`, `while`, `var`
- Symbols: `(`, `)`, `{`, `}`, `=`, `;`
- Identifiers: Strings that start with a letter and are followed by any number of letters or digits.


## **Grammar:** Language Grammar could be defined as follows:

The language has the following grammar:

- `program`: A list of statements.
- `statement`: An if-else statement, a while loop, a for loop, a variable declaration, or an assignment.
- `statements`: A list of statements.
- `expr`: A boolean value, a not expression, a binary operation, or an identifier.


## Files

- `ast.c` and `ast.h`: Define the abstract syntax tree (AST) for the logical expressions.
- `interpreter.c` and `interpreter.h`: Define the interpreter that evaluates the AST.
- `lexer.l`: Defines the lexical analyzer that tokenizes the input.
- `parser.y`: Defines the syntax analyzer that parses the tokens into an AST.
- `main.c`: Contains the main function that ties everything together.
- `Makefile`: Defines the build rules for the project.
- `test.c`: Contains a test program that runs the logic compiler on several test files and checks if the output matches the expected result.

## Features

The logic compiler can:

- Parse and interpret boolean expressions with `AND`, `OR`, and `NOT` operators.
- Handle control flow with `if-else` statements, `while` loops, and `for` loops.
- Declare variables with the `var` keyword and assign values to them.
- Reassign values to variables.

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

## Example Usage 1 ( Declare Variables `var`)

To use the logic compiler, write a logical expression in a text file using the tokens and grammar defined above. Then, run the logic compiler on the file using the command shown in the "Building and Running" section. The logic compiler will print the result of the expression.

Here's an example:

1. Write your logical expression in a text file. For example, you might write the following in a file named `example.txt`:
```text
var x = TRUE;
var y = FALSE;
var z = x OR y;
```

2. Run the logic compiler on the file:

```bash
./logic_compiler example.txt
```

Output:
The logic compiler will print the result of the expression:
```text
Result: 1
```

## Example Usage 2 ( `if-else` Statements)


1. Write your source code in a text file. For example:

```
var x = TRUE;
var y = FALSE;
var z = FALSE;
if (x) then {
    if (y) then {
        z = TRUE;
    } else {
        z = FALSE;
    };
} else {
    z = TRUE;
};
```

2. Run the logic compiler with the source code file as an argument:

```
./logic_compiler your_source_code.txt
```

3. The logic compiler will interpret the source code and print the result of the last expression evaluated:

Here's a step-by-step explanation:

1. Three variables `x`, `y`, and `z` are declared and initialized. `x` is `TRUE`, `y` and `z` are `FALSE`.

2. The first `if` statement checks if `x` is `TRUE`. Since `x` is `TRUE`, the code inside the `then` block is executed.

3. Inside the `then` block, there's another `if` statement that checks if `y` is `TRUE`. Since `y` is `FALSE`, the code inside the `else` block is executed.

4. In the `else` block, `z` is assigned the value `FALSE`.

5. The program ends after executing the `if-else` statement. In this language, the result of the program is the value of the last expression evaluated. In this case, the last expression is `z = FALSE;` inside the `else` block. Since `FALSE` is equivalent to `0`, the result of the program is `0`.

So, the final values of the variables `x`, `y`, and `z` are `TRUE`, `FALSE`, and `FALSE` respectively, and the result of the program is:
```
Result: 0
```

## Example Usage 3 ( `for` Loop)



