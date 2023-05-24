#include "main.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * command_separator - Executes multiple commands separated by semicolons.
 * @input: Input entered by the user
 * Return: 1 if any of the commands fail, and 0 otherwise.
 */
int command_separator(char *input)
{
char *saveptr;
char *token;
int child_status, status = 0;

token = strtok_r(input, ";", &saveptr);
while (token != NULL)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(1);
}
else if (pid == 0) /* child process */
{
/* Tokenize the command to separate command name and arguments */
char *args[64];  /* Assuming maximum 63 arguments + NULL terminator */
int arg_count = 0;

args[arg_count++] = strtok(token, " ");
while (arg_count < 63 && args[arg_count - 1] != NULL)
{
args[arg_count++] = strtok(NULL, " ");
}
args[arg_count] = NULL;  /* Add NULL terminator */

if (execvp(args[0], args) == -1)
{
perror("execvp");
exit(1);  /* Exit child process with error status */
}
}
else /* parent process */
{
waitpid(pid, &child_status, 0); /* wait for child to finish */
if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
{
status = 1; /* set status to 1 if child process fails */
}
}

token = strtok_r(NULL, ";", &saveptr); /* move to next token */
}

return (status);
}

