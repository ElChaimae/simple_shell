#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void exec_cmd(const char **args)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        /* Child process */
        execvp(args[0], (char **) args);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("Fork");
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, "Error executing %s\n", args[0]);
        }
    }
}

