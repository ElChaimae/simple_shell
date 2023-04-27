#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * main - entry point for the shell
 * Return: 0
 */
int main(void)
{
char buffer[BUFFER_SIZE];
char *args[100];
int arg_count;
char *arg;
/* Register signal handler*/
signal(SIGINT, handle_sigint);
/* Set the PATH environment variable */
printf("PATH set successfully\n");
while (1)
{
if (write(STDOUT_FILENO, "$ ", 2) == -1)
{
perror("write");
exit(EXIT_FAILURE);
}
if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
{
break;
}
/*Parse the user input into separate arguments*/
arg_count = 0;
arg = strtok(buffer, " \t\n");
while (arg != NULL && arg_count < 99)
{
args[arg_count] = arg;
arg_count++;
arg = strtok(NULL, " \t\n");
}
args[arg_count] = NULL;
/*Execute the command with the parsed arguments*/
if (arg_count > 0)
{
execute_command(args);
}
}
exit(EXIT_SUCCESS);
}
/**
 * handle_sigint - a function that handles the SIGINT signal
 */
void handle_sigint(int sig_num)
{
(void) sig_num;
fflush(stdout);
write(STDOUT_FILENO, "\n$ ", 3);
}

