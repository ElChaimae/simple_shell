#include "main.h"

/**
 * str_to_long - Converts a string to a long integer
 * @str: The string to convert
 * Return: The converted long integer value
 */
long str_to_long(char *str)
{
long result = 0;
int sign = 1;
char *p = str;

if (*p == '-')
{
sign = -1;
p++;
}
while (*p >= '0' && *p <= '9')
{
result = result * 10 + (*p - '0');
p++;
}
return (sign *result);
}

/**
 * exit_shell - Exits the shell
 * @args: The arguments passed to the shell
 * Return: Always returns 0
 */
int exit_shell(char **args)
{
int status = 0;
char e_msg[100];
int len;

if (args[1] != NULL)
{
status = str_to_long(args[1]);
}
if (status < 0 || status > 255)
{
len = snprintf(e_msg, sizeof(e_msg), "Invalid exit status: %d\n", status);
write(STDERR_FILENO, e_msg, len);
status = 2;
}
exit(status);
}


