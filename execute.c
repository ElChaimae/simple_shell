#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * error - Prints an error message and exits the program
 * @msg: the error message to print
 * Return: nothing
 */
void error(char *msg)
{
perror(msg);
exit(EXIT_FAILURE);
}

/**
 * execute - Executes a given command and handles built-in "cd" command
 * @args: array of strings representing the command and its arguments
 * Return: 0 on success, otherwise error message is printed and program exits
 */
int execute(char **args)
{
char *token;
int i = 0;
int status;

token = strtok(args[0], " \n");
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " \n");
}
args[i] = NULL;
if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
chdir(getenv("HOME"));
else if (chdir(args[1]) == -1)
error("cd failed");
}
else
{
pid_t pid = fork();
if (pid == -1)
error("fork failed");
else if (pid == 0)
{
if (execvp(args[0], args) == -1)
error("execvp failed");
}
else
{
if (wait(&status) == -1)
error("wait failed");
}
}
return (0);
}

