#include "main.h"

/**
 * exit_shell - This function exits the shell.
 * @args: arguments passed
 * Return:0 on success
 */
int exit_shell(char **args)
{
if (args[1] == NULL)
{
write(STDOUT_FILENO, "Exiting Shell...\n", 17);
exit(EXIT_SUCCESS);
}
else if (args[2] != NULL)
{
fprintf(stderr, "Usage: exit [status]\n");
return (1);
}
else
{
int status = atoi(args[1]);
if (status == 0 && strcmp(args[1], "0") != 0)
{
fprintf(stderr, "Invalid exit status: %s\n", args[1]);
return (1);
}
write(STDOUT_FILENO, "Exiting Shell...\n", 17);
exit(status);
}
}

