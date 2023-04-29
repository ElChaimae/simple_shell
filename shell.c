#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "main.h"

#define MAX_ARGS 10

extern char **environ;

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

int execute_command(char** args) {
    int status;
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("exec");
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

#define MAX_OUTPUT_SIZE 1024

char* run_command(char* input) {
    FILE *fp;
    char output[MAX_OUTPUT_SIZE];
    char *result = malloc(MAX_OUTPUT_SIZE * sizeof(char));

    fp = popen(input, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, MAX_OUTPUT_SIZE, fp) != NULL) {
        strcat(result, output);
    }

    pclose(fp);
    return result;
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

