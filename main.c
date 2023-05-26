#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
/**
 * main - entry point for the program
 * @input: user input
 * @alias_list: struct for alias
 * Return: 0 on success
 */

int run_command(char *input, alias_t **alias_list);

int main(void)
{
char *input = NULL;
size_t input_size = 0;
int status = 0;
alias_t *alias_list = NULL;

while (1)
{
if (isatty(fileno(stdin)))
{
write_stdout("$ ", 2);
fflush(stdout);
}
if (getline(&input, &input_size, stdin) == -1)
break;

input[strcspn(input, "\n")] = '\0';

status = run_command(input, &alias_list);

if (isatty(fileno(stdin)) && status != 0)
{
write_stderr("\n", 1);
}

free(input);    /* Free the allocated memory after each iteration */
input = NULL;   /* Reset the input pointer to NULL */
input_size = 0; /* Reset the input size to 0 */
}

free(input); /* Free the input variable before exiting */
return (status);
}

