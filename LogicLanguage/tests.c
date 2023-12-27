#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void test_interpret(const char* filename, int expected) {
    printf("Running test: %s\n", filename);

    char command[256];
    sprintf(command, "./logic_compiler %s", filename);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("popen failed\n");
        exit(1);
    }

    char buffer[256];
    int result;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        int temp;
        if (sscanf(buffer, "Result: %d", &temp) == 1) {
            result = temp;
        }
    }
    pclose(pipe);

    printf("Result: %d\n", result);
    assert(result == expected);
}

int main() {
    // Existing tests
    printf("\nRunning declaration and reassignment tests...\n");
    test_interpret("testsfiles/declaration_tests/test_var_declaration.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_reassignment.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_expression.txt", 0);
    test_interpret("testsfiles/declaration_tests/test_var_usage.txt", 1);
    test_interpret("testsfiles/declaration_tests/test_var_multiple.txt", 1);

    // New if-else tests
    printf("\nRunning if-else statement tests...\n");
    test_interpret("testsfiles/if-else_tests/logical_op_if-else.txt", 0);
    test_interpret("testsfiles/if-else_tests/nested_if-else.txt", 0);
    test_interpret("testsfiles/if-else_tests/simple_if-else.txt", 1);

    // New loop tests
    printf("\nRunning loop tests...\n");
    test_interpret("testsfiles/loop_tests/for_loop.txt", 0);
    test_interpret("testsfiles/loop_tests/while_loop.txt", 0);

    printf("\nAll tests passed!\n");
    return 0;
}