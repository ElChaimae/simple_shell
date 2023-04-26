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
  int status = 0;

  if (dir == NULL)
  {
    dir = getenv("HOME");
    if (dir == NULL)
    {
      write(STDERR_FILENO, "cd: no home directory found\n", 28);
      status = 1;
    }
  }
  else if (strcmp(dir, "-") == 0)
  {
    dir = getenv("OLDPWD");
    if (dir == NULL)
    {
      write(STDERR_FILENO, "cd: no previous directory found\n", 33);
      status = 1;
    }
    else
    {
      write(STDOUT_FILENO, dir, strlen(dir));
      write(STDOUT_FILENO, "\n", 1);
    }
  }

  if (status != 1 && chdir(dir) != 0)
  {
    perror("cd");
    status = 1;
  }

  if (status != 1 && getcwd(cwd, PATH_MAX) == NULL)
  {
    perror("getcwd");
    status = 1;
  }

  if (status != 1 && setenv("PWD", cwd, 1) != 0)
  {
    perror("setenv");
    status = 1;
  }

  return status;
}

