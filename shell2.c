#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

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
    char** args;
    int result;
    char *env_value, *path, *dir;
    char command_path[256];
    int command_found = 0;

    args = parse_args(input);

    if (args[0] == NULL) {
        free_args(args);
        return 0;
    }

    if (strcmp(args[0], "exit") == 0) {
        free_args(args);
        exit(0);
    } else if (strcmp(args[0], "env") == 0) {
        for (env_value = *environ; env_value; env_value = *(environ++)) {
            write_stdout(env_value, strlen(env_value));
            write_stdout("\n", 1);
        }
        free_args(args);
        return 0;
    }

    if (args[0][0] == '.' || args[0][0] == '/') {
        if (access(args[0], X_OK) == 0) {
            command_found = 1;
        } else {
            write_stderr("./hsh: 1: ", 13);
            write_stderr(args[0], strlen(args[0]));
            write_stderr(": not found\n", 12);
            free_args(args);
            return -1;
        }
    } else {
        path = getenv("PATH");
        if (path == NULL) {
            write_stderr("error: PATH environment variable not set\n", 40);
            free_args(args);
            return -1;
        }
        dir = strtok(path, ":");
        while (dir && !command_found) {
            strncpy(command_path, dir, sizeof(command_path) - 1);
            command_path[sizeof(command_path) - 1] = '\0';
            strncat(command_path, "/", sizeof(command_path) - strlen(command_path) - 1);
            strncat(command_path, args[0], sizeof(command_path) - strlen(command_path) - 1);
            if (access(command_path, X_OK) == 0) {
                args[0] = strdup(command_path);
                command_found = 1;
            } else {
                dir = strtok(NULL, ":");
            }
        }
    }

    if (!command_found) {
        write_stderr("./hsh: 1: ", 13);
        write_stderr(args[0], strlen(args[0]));
        write_stderr(": not found\n", 12);
        free_args(args);
        return -1;
    }

    result = execute_command(args);

    free_args(args);
    return result;
}

