#define MAX_PATH_LENGTH 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


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

