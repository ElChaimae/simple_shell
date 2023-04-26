#include "main.h"
/**
 * command_separator - executes multiple commands separated by semicolons.
 * @input: input entered by user
 * Return: 1 if any of the commands fail, and 0 otherwise.
 */
int command_separator(char *input)
{
char *saveptr;
char *token = strtok_r(input, ";", &saveptr);
int status = 0;

while (token != NULL)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(1);
}
else if (pid == 0)
{
char *args[3];
args[0] = token;
args[1] = NULL;
execve(token, args, NULL);
perror("execve");
_exit(1);
}
else
{
int child_status;
waitpid(pid, &child_status, 0);
if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
{
status = 1;
}
}
token = strtok_r(NULL, ";", &saveptr);
}
return (status);
}

