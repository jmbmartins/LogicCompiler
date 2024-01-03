// Include the necessary header files.
#include <stdio.h>
#include "interpreter.h"
#include "ast.h"  

// The main function takes command-line arguments.
int main(int argc, char** argv) {
    // If the number of arguments is not 2 (the program name and the filename), print a usage message and return 1.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Call the interpret function with the filename argument.
    int result = interpret(argv[1]);
    // If the interpret function returns -1, print an error message and return 1.
    if (result == -1) {
        fprintf(stderr, "Error interpreting file\n");
        return 1;
    }

    // Print the result of the interpretation.
    printf("Result: %d\n", result);

    // Return 0 to indicate successful execution.
    return 0;
}