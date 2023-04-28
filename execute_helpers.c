#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

void execute_child(char **args) {
    pid_t pid = fork();
    if (pid == 0) {  /*child process*/
        execvp(args[0], args);
        fprintf(stderr, "Error: failed to execute command '%s'\n", args[0]);
        exit(1);
    } else if (pid < 0) {  /*error*/
        fprintf(stderr, "Error: failed to fork process\n");
        exit(1);
    }
}

void wait_for_child(pid_t pid, int *status) {
    if (waitpid(pid, status, 0) == -1) {
        fprintf(stderr, "Error: failed to wait for child process\n");
        exit(1);
    }
}

