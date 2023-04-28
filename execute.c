#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

int execute(char **args, char *const env[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        /*Child process*/
        if (execve(args[0], args, env) == -1) {
            perror("execve");
            return EXIT_FAILURE;
        }
    } else {
        /*Parent process*/
        do {
            if (waitpid(pid, &status, WUNTRACED) == -1) {
                perror("waitpid");
                return EXIT_FAILURE;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));

        if (WIFSTOPPED(status)) {
            fprintf(stderr, "Child process stopped by signal: %d\n", WSTOPSIG(status));
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

