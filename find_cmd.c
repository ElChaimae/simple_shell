#define MAX_PATH_LENGTH 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * find_command - Find the full path of a command in PATH directories.
 * @cmd: The name of the command to find.
 * Return: On success, returns a pointer to the full path of the command.
 * On failure, returns NULL.
 */
char *find_command(char *cmd, char *command_path)
{
char *path;
char *dir;

path = getenv("PATH");

if (path == NULL)
return (NULL);

dir = strtok(path, ":");
while (dir)
{
snprintf(command_path, MAX_PATH_LENGTH, "%s/%s", dir, cmd);

if (access(command_path, X_OK) == 0)
return (command_path);

dir = strtok(NULL, ":");
}

return (NULL);
}

