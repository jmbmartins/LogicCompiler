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
    test_interpret("testsfiles/test_var_declaration.txt", 1);
    test_interpret("testsfiles/test_var_reassignment.txt", 1);
    test_interpret("testsfiles/test_var_expression.txt", 0);
    test_interpret("testsfiles/test_var_usage.txt", 1);
    test_interpret("testsfiles/test_var_multiple.txt", 1);
    printf("All tests passed!\n");
    return 0;
}