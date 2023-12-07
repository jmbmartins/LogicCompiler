#include <stdio.h>
#include "ast.h"
extern FILE* yyin;
extern int yyparse();
extern Node* parse_tree;
int evaluate(Node* node); // Declare evaluate

int interpret(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return -1;
    }

    yyin = fp;
    if (yyparse() != 0) {
        fprintf(stderr, "Parse error\n");
        return -1;
    }

    fclose(fp);

    int result = evaluate(parse_tree);
    return result;
}