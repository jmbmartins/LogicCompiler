// Include the necessary header files.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Define the test function.
void test_interpret(const char* filename, int expected) {
    printf("Running test: %s\n", filename);

    // Prepare the command to run the compiler.
    char command[256];
    sprintf(command, "./logic_compiler %s", filename);

    // Open a pipe to the compiler process.
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("popen failed\n");
        exit(1);
    }

    // Read the output of the compiler.
    char buffer[256];
    int result;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        int temp;
        if (sscanf(buffer, "Result: %d", &temp) == 1) {
            result = temp;
        }
    }
    pclose(pipe);

    // Print and check the result.
    printf("Result: %d\n", result);
    assert(result == expected);
}

// Define the main function that runs all the tests.
int main() {
    // Run the declaration tests.
    printf("\nRunning declaration and reassignment tests...\n");
    test_interpret("testsfiles/declaration_tests/test_var_declaration.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_reassignment.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_expression.txt", 0);
    test_interpret("testsfiles/declaration_tests/test_var_usage.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_multiple.txt", 1);

    // Run the new if-else tests.
    printf("\nRunning if-else statement tests...\n");
    test_interpret("testsfiles/if-else_tests/logical_op_if-else.txt", 0);
    test_interpret("testsfiles/if-else_tests/nested_if-else.txt", 0);
    test_interpret("testsfiles/if-else_tests/simple_if-else.txt", 1);

    // Run the new loop tests.
    printf("\nRunning loop tests...\n");
    test_interpret("testsfiles/loop_tests/for_loop.txt", 0);
    test_interpret("testsfiles/loop_tests/while_loop.txt", 0);

    // Print a success message.
    printf("\nAll tests passed!\n");
    return 0;
}