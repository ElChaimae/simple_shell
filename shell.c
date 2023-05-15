#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>




void write_stdout(const char* message, size_t len) {
    write(STDOUT_FILENO, message, len);
}

void write_stderr(const char* message, size_t len) {
    write(STDERR_FILENO, message, len);
}


void free_args(char** args) {
    int i;

    if (args) {
        for (i = 0; args[i]; i++) {
            free(args[i]);
        }
        free(args);
    }
}

char** parse_args(char* input) {
    char** args = malloc((MAX_ARGS + 1) * sizeof(char*));
    int arg_count = 0;
    char *arg;

    if (!args) {
        perror("malloc");
        exit(1);
    }
    arg = strtok(input, " \t\n\r");
    while (arg && arg_count < MAX_ARGS) {
        args[arg_count++] = strdup(arg);
        arg = strtok(NULL, " \t\n\r");
    }
    args[arg_count] = NULL;
    return args;
}

