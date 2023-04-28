#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define PROMPT "> "

char *get_command_path(char *command)
{
    char *path = getenv("PATH");
    char *token;
    char *path_component;
    char *command_path = NULL;
    int found_command = 0;

    if (path == NULL)
        return NULL;

    path = strdup(path);
    if (path == NULL)
        return NULL;

    token = strtok(path, ":");
    while (token != NULL && !found_command)
    {
        path_component = malloc(strlen(token) + strlen(command) + 2);
        if (path_component == NULL) {
            free(path);
            return NULL;
        }
        sprintf(path_component, "%s/%s", token, command);
        if (access(path_component, F_OK) == 0)
        {
            command_path = path_component;
            found_command = 1;
        }
        else {
            free(path_component);
        }
        token = strtok(NULL, ":");
    }

    free(path);
    if (!found_command) {
        return NULL;
    }
    return command_path;
}

int execute_command(char *command)
{
    int argc = 0;
    char *args[MAX_ARGUMENTS + 2]; /* +2 for command and NULL terminator*/
    char *token;
    char *command_path;
    pid_t pid;
    int status;

    token = strtok(command, " \t\n");
    while (token != NULL && argc < MAX_ARGUMENTS)
    {
        args[argc] = token;
        argc++;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;

    if (argc == 0)
        return 0;

    command_path = get_command_path(args[0]);
    if (command_path == NULL)
    {
        printf("%s: command not found\n", args[0]);
        return 0;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error forking process");
        free(command_path);
        return -1;
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execv(command_path, args) == -1)
        {
            perror("Error executing command");
            free(command_path);
            exit(EXIT_FAILURE);
        }
        free(command_path);
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* Parent process */
        do
        {
            if (waitpid(pid, &status, WUNTRACED) == -1)
            {
                if (errno == EINTR)
                    continue;
                perror("Error waiting for child process");
                free(command_path);
                return -1;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(command_path);
    return 0;
}
