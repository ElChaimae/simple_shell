#include "main.h"

/**
 * execute -This function executes a command
 * @command: command entered by user
 * Return: the exit status.
 */
int execute(char *command)
{
int status = system(command);
return (status);
}


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
status = execute(token);
next_command = 0;
}
}
token = strtok(NULL, " ");
}
return (status);
}

