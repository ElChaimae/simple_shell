#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

int run_command(char* input);

int main() {
    char input[MAX_INPUT_SIZE];
    int result;

    while(1) {
        printf("$");
        if(fgets(input, MAX_INPUT_SIZE, stdin) == NULL) break;
        input[strlen(input)-1] = '\0';
        result = run_command(input);
        if(result) break;
    }

    return 0;
}

