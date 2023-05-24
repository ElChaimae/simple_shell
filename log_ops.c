#include "main.h"

extern char **environ;

int execute_command(char **args);

/**
 * logical_operators - Executes a command with support for shell logical operators && and ||.
 * @input: User input
 * Return: 1 if any of the commands fail, and 0 otherwise.
 */
int logical_operators(char *input)
{
int status = 0;
int next_command = 1;
char *token;
char **args = NULL;
const char *delimiters = " \t\n";

token = strtok(input, delimiters);
while (token != NULL)
{
if (strcmp(token, "&&") == 0)
{
next_command = (status == 0) ? 1 : 0;
}
else if (strcmp(token, "||") == 0)
{
next_command = (status != 0) ? 1 : 0;
}
else
{
if (next_command)
{
args = realloc(args, sizeof(char *) * 2);
args[0] = token;
args[1] = NULL;
status = execute_command(args);
next_command = 0;
}
}
token = strtok(NULL, delimiters);
}

free(args);

return (status);
}

