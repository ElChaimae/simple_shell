#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * write_stdout - Writes a message to the standard output (stdout).
 * @message: The message to be printed.
 * @len: The length of the message.
 */
void write_stdout(const char *message, size_t len)
{
    write(STDOUT_FILENO, message, len);
}


/**
 * write_stderr - Writes an error message to the standard error (stderr).
 * @message: The error message to be printed.
 * @len: The length of the error message.
 */
void write_stderr(const char *message, size_t len)
{
    write(STDERR_FILENO, message, len);
}


/**
 * parse_args - parses arguments
 * @input: user input
 * Return: 0
 */
char **parse_args(char *input)
{
char **args = malloc((MAX_ARGS + 1) * sizeof(char *));
int arg_count = 0;
char *arg;

if (!args)
{
perror("malloc");
exit(1);
}

while (*input)
{
while (*input && (*input == ' ' || *input == '\t'))
input++;

if (*input == '\0' || *input == '\n')
break;

if (*input == '"')
{
input++;
arg = input;
while (*input && *input != '"')
input++;
}
else
{
arg = input;
while (*input && *input != ' ' && *input != '\t')
input++;
}

if (*input)
*input++ = '\0';

args[arg_count++] = strdup(arg);

if (arg_count >= MAX_ARGS)
break;
}

args[arg_count] = NULL;
return (args);
}


/**
 * free_args - Frees the memory allocated for a null-terminated
 * array of strings.
 * @args: The array of strings to be freed.
 */
void free_args(char **args)
{
int i;

if (args)
{
for (i = 0; args[i]; i++)
free(args[i]);

free(args);
}
}


