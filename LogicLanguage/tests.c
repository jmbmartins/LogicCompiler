// tests.c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void test_interpret(const char* filename, int expected) {
    char command[256];
    sprintf(command, "./logic_compiler %s", filename);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("popen failed\n");
        exit(1);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), pipe);
    pclose(pipe);

    int result;
    sscanf(buffer, "Result: %d", &result);
    printf("Result: %d\n", result);
    assert(result == expected);
}

int main() {
    test_interpret("testsfiles/test1.txt", 1);  
    test_interpret("testsfiles/test2.txt", 0);
    test_interpret("testsfiles/test3.txt", 0);
    printf("All tests passed!\n");
    return 0;
}