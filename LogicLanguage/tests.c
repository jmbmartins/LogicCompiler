#include <assert.h>
#include "interpreter.h"
#include <stdio.h>

void test_evaluate() {
    // Test boolean values
    assert(interpret("TRUE") == 1);
    assert(interpret("FALSE") == 0);

    // Test NOT operation
    assert(interpret("NOT TRUE") == 0);
    assert(interpret("NOT FALSE") == 1);

    // Test AND operation
    assert(interpret("TRUE AND FALSE") == 0);
    assert(interpret("TRUE AND TRUE") == 1);

    // Test OR operation
    assert(interpret("TRUE OR FALSE") == 1);
    assert(interpret("FALSE OR FALSE") == 0);
}

void test_conditional() {
    // Test if-else with true condition
    assert(interpret("if (TRUE) { TRUE } else { FALSE }") == 1);

    // Test if-else with false condition
    assert(interpret("if (FALSE) { TRUE } else { FALSE }") == 0);
}

void test_loops() {
    // Test while loop that runs once
    assert(interpret("var x = TRUE; while (x) { x = FALSE } x") == 0);

    // Test for loop that runs 5 times
    assert(interpret("for (var x = 0; x < 5; x = x + 1) { } x") == 5);
}

void test_variables() {
    // Test variable assignment and retrieval
    assert(interpret("var x = TRUE; x") == 1);
    assert(interpret("var x = FALSE; x") == 0);
}

int main() {
    test_evaluate();
    test_conditional();
    test_loops();
    test_variables();
    printf("All tests passed!\n");
    return 0;
}