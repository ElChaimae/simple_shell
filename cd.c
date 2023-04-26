#include "main.h"
/**
 * cd - This function changes the current directory of the process.
 * @args: number of arguments
 * Return: 0 on success, 1 on failure
 */
int cd(char **args)
{
char *dir = args[1];
char cwd[PATH_MAX];
if (dir == NULL)
{
dir = getenv("HOME");
if (dir == NULL)
{
fprintf(stderr, "cd: no home directory found\n");
return (1);
}
}
else if (strcmp(dir, "-") == 0)
{
dir = getenv("OLDPWD");
if (dir == NULL)
{
fprintf(stderr, "cd: no previous directory found\n");
return (1);
}
printf("%s\n", dir);
}
if (chdir(dir) != 0)
{
perror("cd");
return (1);
}
if (getcwd(cwd, PATH_MAX) == NULL)
{
perror("getcwd");
return (1);
}
if (setenv("PWD", cwd, 1) != 0)
{
perror("setenv");
return (1);
}
return (0);
}

