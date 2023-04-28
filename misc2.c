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
char *command_path;
char *path_env = NULL, *path = NULL, *dir = NULL;
int i;
size_t command_len = strlen(command), dir_len = 0, path_len = 0;
char separator[2] = { '/', '\0' };

for (i = 0; envp[i] != NULL && path_env == NULL; i++)
if (strncmp(envp[i], "PATH=", 5) == 0)
path_env = envp[i] + 5;
if (path_env != NULL)
{
dir = strtok(path_env, ":");
while (dir != NULL && path == NULL)
{
dir_len = strlen(dir);
path_len = dir_len + command_len + 2;
command_path = malloc(path_len);
if (command_path == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
strcpy(command_path, dir);
strcat(command_path, separator);
strcat(command_path, command);
if (access(command_path, X_OK) == 0)
path = command_path;
else
free(command_path);
dir = strtok(NULL, ":");
}
}
return (path);
}

