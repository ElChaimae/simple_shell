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
        exit(127);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return -1;
    }
}


int run_command(char* input) {
    char** args;
    int result;
    char* path;
    char* dir;
    char command_path[1024];
    int command_found = 0;
    char** env_value;

    args = parse_args(input);

    if (!args[0]) {
        free_args(args);
        return 0;
    }

    if (strcmp(args[0], "exit") == 0) {
        int exit_status = 0;
        if (args[1]) {
            exit_status = atoi(args[1]);
        }
        free_args(args);
        exit(exit_status);
    } else if (strcmp(args[0], "env") == 0) {
        for (env_value = environ; *env_value; env_value++) {
            write_stdout(*env_value, strlen(*env_value));
            write_stdout("\n", 1);
        }
        free_args(args);
        return 0;
    } else if (strcmp(args[0], "setenv") == 0) {
        if (args[1] && args[2]) {
            if (setenv(args[1], args[2], 1) == -1) {
                perror("setenv");
            }
        } else {
            write_stderr("setenv: Invalid syntax. Usage: setenv VARIABLE VALUE\n", 54);
        }
        free_args(args);
        return 0;
    } else if (strcmp(args[0], "unsetenv") == 0) {
        if (args[1]) {
            if (unsetenv(args[1]) == -1) {
                perror("unsetenv");
            }
        } else {
            write_stderr("unsetenv: Invalid syntax. Usage: unsetenv VARIABLE\n", 51);
        }
        free_args(args);
        return 0;
    }

    if (args[0][0] == '.' || args[0][0] == '/' || args[0][0] == '~') {
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
            write_stderr("./hsh: 1: ", 10);
            write_stderr(args[0], strlen(args[0]));
            write_stderr(": not found\n", 12);
            free_args(args);
            return 127;
        }
        dir = strtok(path, ":");
        while (dir && !command_found) {
            snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
            if (access(command_path, X_OK) == 0) {
                args[0] = strdup(command_path);
                command_found = 1;
            } else {
                /* Add condition to check if access fails for the original command */
                snprintf(command_path, sizeof(command_path), "/bin/%s", args[0]);
                if (access(command_path, X_OK) == 0) {
                    args[0] = strdup(command_path);
                    command_found = 1;
                } else {
                    dir = strtok(NULL, ":");
                }
            }
        }
    }

    if (!command_found) {
        write_stderr("./hsh: 1: ", 10);
        write_stderr(args[0], strlen(args[0]));
        write_stderr(": not found\n", 12);
        free_args(args);
        return 127;
    }

    result = execute_command(args);

    free_args(args);
    return result;
}

