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

### Test Files:

- `declaration_tests/test_var_declaration.txt`: Tests variable declaration.
- `declaration_tests/test_var_expression.txt`: Tests using variables in expressions.
- `declaration_tests/test_var_multiple.txt`: Tests declaring multiple variables.
- `declaration_tests/test_var_reassignment.txt`: Tests reassigning a value to a variable.
- `declaration_tests/test_var_usage.txt`: Tests using a variable after it has been declared.

- `if-else_tests/logical_op_if-else.txt`: Tests using logical operators in if-else conditions.
- `if-else_tests/nested_if-else.txt`: Tests nested if-else statements.
- `if-else_tests/simple_if-else.txt`: Tests simple if-else statements.

- `loop_tests/for_loop.txt`: Tests for loops.
- `loop_tests/while_loop.txt`: Tests while loops.

Each of these test files contains source code in the logic language presented. The test program runs the logic compiler on each file and checks if the output matches the expected result. If the output does not match, the test fails and the program prints an error message.

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

1. Write your source code in a text file. For example:

```
var y = FALSE;
for (var x = TRUE; x; x = FALSE) {
    y = TRUE;
};
```

2. Run the logic compiler with the source code file as an argument:

```
./logic_compiler your_source_code.txt
```

3. The logic compiler will interpret the source code and print the result of the last expression evaluated:

Here's a step-by-step explanation:

1. A variable `y` is declared and initialized to `FALSE`.

2. A `for` loop is started with a new variable `x` declared and initialized to `TRUE`. The loop condition is `x`, and the loop update is `x = FALSE`.

3. Inside the `for` loop, `y` is assigned the value `TRUE`.

4. On the next iteration, `x` is set to `FALSE` as per the loop update. Since the loop condition `x` is now `FALSE`, the loop ends.

5. The program ends after executing the `for` loop. In this language, the result of the program is the value of the last expression evaluated. In this case, the last expression is `x = FALSE;` in the loop update. Since `FALSE` is equivalent to `0`, the result of the program is `0`.

So, the final values of the variables `x` and `y` are `FALSE` and `TRUE` respectively, and the result of the program is:
```
Result: 0
```


## Example Usage 4 ( `while` Loop)

1. Write your source code in a text file. For example:

```
var counter = TRUE;
var sum = FALSE;
while (counter) {
    sum = TRUE;
    counter = FALSE;
};
```

2. Run the logic compiler with the source code file as an argument:

```
./logic_compiler your_source_code.txt
```

3. The logic compiler will interpret the source code and print the result of the last expression evaluated:

Here's a step-by-step explanation:

1. Two variables `counter` and `sum` are declared and initialized. `counter` is `TRUE` and `sum` is `FALSE`.

2. A `while` loop is started with the condition `counter`.

3. Inside the `while` loop, `sum` is assigned the value `TRUE` and `counter` is set to `FALSE`.

4. On the next iteration, since the loop condition `counter` is now `FALSE`, the loop ends.

5. The program ends after executing the `while` loop. In this language, the result of the program is the value of the last expression evaluated. In this case, the last expression is `counter = FALSE;` inside the `while` loop. Since `FALSE` is equivalent to `0`, the result of the program is `0`.

So, the final values of the variables `counter` and `sum` are `FALSE` and `TRUE` respectively, and the result of the program is:
```
Result: 0
```

