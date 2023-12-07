#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char* files[] = {"testsfiles/test1.txt", "testsfiles/test2.txt", "testsfiles/test3.txt", "testsfiles/test4.txt", "testsfiles/test5.txt", "testsfiles/test6.txt", "testsfiles/test7.txt"};
    int expected_results[] = {1, 0, 1, 0, 1, 0, 1};

    for(int i = 0; i < sizeof(files)/sizeof(files[0]); i++) {
        char command[50];
        sprintf(command, "./logic_compiler %s", files[i]);
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }

        while ((read = getline(&line, &len, fp)) != -1) {
            printf("Output of %s: %s", files[i], line);
            int result = atoi(line + 8); // get the integer result from the output line
            if(result == expected_results[i]) {
                printf("Test passed\n");
            } else {
                printf("Test failed\n");
            }
        }

        pclose(fp);
    }

    if (line)
        free(line);

    return 0;
}