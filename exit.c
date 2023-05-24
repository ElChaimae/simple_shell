#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * str_to_long - Converts a string to a long integer
 * @str: The string to convert
 * Return: The converted long integer value, or -1 on error
 */
long str_to_long(char *str)
{
char *endptr;
long result;

result = strtol(str, &endptr, 10);
if (*endptr != '\0')
{
fprintf(stderr, "Invalid exit status: %s\n", str);
return (-1);
}

return (result);
}

/**
 * exit_shell - Exits the shell
 * @args: The arguments passed to the shell
 * Return: Always returns 0
 */
int exit_shell(char **args)
{
int status = 0;

if (args[1] != NULL)
{
status = (int)str_to_long(args[1]);
if (status == -1)
{
return (1); /*Return non-zero value to indicate error*/
}
}

exit(status);
}

