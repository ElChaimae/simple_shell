#include "main.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * str_to_long - handles negative numbers and ignores leading whitespace
 * and non-digit characters.
 * @str: string to convert
 * Return: corresponding long integer value
 */
long str_to_long(const char *str)
{
long result = 0;
int sign = 1;
const char *p = str;

if (*p == '-')
{
sign = -1;
p++;
}
else if (*p == '+')
}
p++;
}
while (*p >= '0' && *p <= '9')
{
result = result * 10 + (*p - '0');
p++;
}
return (sign * result);
}

/**
 * my_atoi - Converts a string to an integer.
 * @s: The input string.
 * Return: The integer value of the string.
 */
int my_atoi(const char *s)
{
int result = 0;
int sign = 1;
int i = 0;

if (s == NULL || *s == '\0')
{
char *error_message = "Error: input string is empty or NULL.\n";
write(STDERR_FILENO, error_message, strlen(error_message));
return (-1);
}
if (*s == '-')
{
sign = -1;
i++;
}
while (s[i] != '\0')
{
if (!isdigit(s[i]))
{
char *error_message = "Error: input string contains non-digit characters.\n";
write(STDERR_FILENO, error_message, strlen(error_message));
return (-1);
}
result = result * 10 + (s[i] - '0');
i++;
}
result *= sign;
if (result < 0 || result > 255)
{
char *error_message = "Error: converted value is out of range.\n";
write(STDERR_FILENO, error_message, strlen(error_message));
return (-1);
}
return (result);
}

/**
 * exit_shell - This function exits the shell.
 * @args: arguments passed
 * Return: 0 on success
 */
int exit_shell(char **args)
{
char *message;

if (args[1] == NULL)
{
message = "Exiting Shell...\n";
write(STDOUT_FILENO, message, strlen(message));
exit(EXIT_SUCCESS);
}
else if (args[2] != NULL)
{
char *error_message = "Usage: exit [status]\n";
write(STDERR_FILENO, error_message, strlen(error_message));
return (EXIT_FAILURE);
}
else
{
long status = str_to_long(args[1]);
if (status < 0 || status > 255)
{
char error_message[100];
size_t len = snprintf(error_message, sizeof(error_message), "Invalid exit status: %s\n", args[1]);
write(STDERR_FILENO, error_message, len);
return (EXIT_FAILURE);
}
message = "Exiting Shell...\n";
write(STDOUT_FILENO, message, strlen(message));
exit((int) status);
}
}

