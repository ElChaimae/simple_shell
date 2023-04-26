#include "main.h"
#include <sys/wait.h>

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
    char *args[100];
    int i = 0;

    while (token != NULL)
    {
        if (token[0] == '&' && token[1] == '&')
        {
            next_command = (status == 0) ? 1 : 0;
        }
        else if (token[0] == '|' && token[1] == '|')
        {
            next_command = (status != 0) ? 1 : 0;
        }
        else
        {
            if (next_command)
            {
                args[i++] = token;
                args[i] = NULL;
                status = execute(args);
                next_command = 0;
                i = 0;
            }
            else
            {
                args[i++] = token;
                args[i] = NULL;
            }
        }
        token = strtok(NULL, " ");
    }
    return status;
}

