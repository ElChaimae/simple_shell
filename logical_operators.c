#include "main.h"

int execute(char **args);

/**
 * logical_operators - executes a command with support for shell logical
 * operators && and ||.
 * @input: user input
 * Return: 1 if any of the commands fail, and 0 otherwise.
 */
int logical_operators(char *input)
{
int status = 0;
int next_command = 1;
char *token = strtok(input, " ");
char **args = NULL;

while (token != NULL)
{
if (strcmp(token, "&&") == 0)
{
next_command = (status == 0) ? 1 : 0;
}
else if
(strcmp(token, "||") == 0)
{
next_command = (status != 0) ? 1 : 0;
}
else
{
if (next_command)
{
status = execute(args);
next_command = 0;
}
}
token = strtok(NULL, " ");
}
return (status);
}


