#include <stdio.h>
#include "interpreter.h"
#include "ast.h"  // or the appropriate header file

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    int result = interpret(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Error interpreting file\n");
        return 1;
    }

    printf("Result: %d\n", result);

    return 0;
}