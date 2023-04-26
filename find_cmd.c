#include "main.h"

/**
 * get_path_value - Get the PATH environment variable.
 *
 * Return: On success, returns a pointer to the PATH environment variable.
 * On failure, returns NULL.
 */
char *get_path_value(void)
{
char *path = _getenv("PATH");

if (!path)
{
perror("Unable to get PATH");
return (NULL);
}

return (path);
}

/**
 * allocate_full_path - Allocate memory for the full path of a command.
 * @path: The PATH environment variable.
 * @cmd: The name of the command.
 *
 * Return: On success, returns a pointer to the full path of the command.
 * On failure, returns NULL.
 */
char *allocate_full_path(char *path, char *cmd)
{
char *full_path = malloc(strlen(path) + strlen(cmd) + 2);

if (!full_path)
{
perror("Unable to allocate memory");
return (NULL);
}

strcpy(full_path, path);
strcat(full_path, "/");
strcat(full_path, cmd);

return (full_path);
}


/**
 * find_in_directory - Find the command in a directory.
 * @dir: The directory to search.
 * @cmd: The name of the command.
 * @full_path: The full path of the command.
 *
 * Return: On success, returns 1.
 * On failure, returns 0.
 */
int find_in_directory(char *dir, char *cmd, char *full_path)
{
int i = 0;

while (*dir)
{
if (*dir == ':')
{
full_path[i++] = '/';
strcpy(&full_path[i], cmd);
if (access(full_path, X_OK) == 0)
return (1);
i = 0;
}
else
{
full_path[i++] = *dir;
}
dir++;
}

return (0);
}

/**
 * find_command - Find the full path of a command in PATH directories.
 * @cmd: The name of the command to find.
 *
 * Return: On success, returns a pointer to the full path of the command.
 * On failure, returns NULL.
 */
char *find_command(char *cmd)
{
char *path, *full_path;

/* Get the PATH environment variable */
path = get_path_value();
if (!path)
{
return (NULL);
}

/* Allocate memory for the full path */
full_path = allocate_full_path(path, cmd);
if (!full_path)
{
free(path);
return (NULL);
}

/* Iterate through PATH directories to find the command */
if (!find_in_directory(path, cmd, full_path))
{
fprintf(stderr, "%s: command not found\n", cmd);
free(full_path);
full_path = NULL;
}

free(path);

return (full_path);
}

