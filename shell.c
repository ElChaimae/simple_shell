#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>


#define MAX_ARGS 10

void free_args(char** args);

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
        execve(args[0], args, environ);
        perror("execve");
        _exit(1);
    } else {
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}


int run_command(char* input) {
    char** args = parse_args(input);
    int result;
    char *env_value, *path, *dir;
    char command_path[256];
    int command_found = 0;

    if (args[0] == NULL) {
        free_args(args);
        return 0;
    }

    if (strcmp(args[0], "exit") == 0) {
        free_args(args);
        exit(0);
    } else if (strcmp(args[0], "env") == 0) {
        for (env_value = *environ; env_value; env_value = *(environ++)) {
            printf("%s\n", env_value);
        }
        free_args(args);
        return 0;
    }

    if (args[0][0] == '.' || args[0][0] == '/') {
        if (access(args[0], X_OK) == 0) {
            command_found = 1;
        } else {
            fprintf(stderr, "%s: 1: %s: not found\n", "./hsh", args[0]);
            free_args(args);
            return -1;
        }
    } else {
        path = getenv("PATH");
        if (!path) {
            fprintf(stderr, "error: PATH environment variable not set\n");
            free_args(args);
            return -1;
        }
        dir = strtok(path, ":");
        while (dir && !command_found) {
            snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
            if (access(command_path, X_OK) == 0) {
                args[0] = strdup(command_path);
                command_found = 1;
            } else {
                dir = strtok(NULL, ":");
            }
        }
    }

    if (!command_found) {
        fprintf(stderr, "%s: 1: %s: not found\n", "./hsh", args[0]);
        free_args(args);
        return -1;
    }

    result = execute_command(args);

    if (strcmp(args[0], "exit") != 0) {
        printf("$ ");
        fflush(stdout);
    }

    free_args(args);
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

