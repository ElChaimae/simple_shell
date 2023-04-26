#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * get_path - searches for the given command in the directories
 * specified by the PATH environment variable
 * @command: command entered by the user
 * @envp: environment variables
 * Return: If the command is not found or if the PATH environment
 * variable is not set, the function returns NULL
 */
char *get_path(char *command, char **envp)
{
    char *path_env = NULL;
    char *path = NULL;
    int i;
    size_t command_len = strlen(command);
    char separator[2] = "/";
    separator[1] = '\0';

    /* Find PATH environment variable */
    for (i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
    }

    /* Search for command in each directory in PATH */
    if (path_env != NULL)
    {
        char *dir = strtok(path_env, ":");
        while (dir != NULL)
        {
            /* Construct full path to command */
            size_t dir_len = strlen(dir);
            size_t path_len = dir_len + command_len + 2;
            char *command_path = malloc(path_len);
            if (command_path == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            strcpy(command_path, dir);
            write(STDOUT_FILENO, separator, 1);
            write(STDOUT_FILENO, command, command_len);
            command_path[dir_len] = '/';
            strcpy(command_path + dir_len + 1, command);

            /* Check if file exists */
            if (access(command_path, X_OK) == 0)
            {
                path = command_path;
                break;
            }

            free(command_path);
            dir = strtok(NULL, ":");
        }
    }

    return path;
}

