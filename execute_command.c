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

int custom_strcmp(const char *s1, const char *s2);

/**
 * execute_command - Executes a given command and handles built-in "cd" command
 * @args: array of strings representing the command and its arguments
 * Return: 0 on success, otherwise error message is printed and program exits
 */
int execute_command(char **args)
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
if (custom_strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
chdir(getenv("HOME"));
else if (chdir(args[1]) == -1)
perror("cd failed");
}
else
{
pid_t pid = fork();
if (pid == -1)
perror("fork failed");
else if (pid == 0)
{
if (execvp(args[0], args) == -1)
perror("execvp failed");
}
else
{
if (wait(&status) == -1)
perror("wait failed");
}
}
return (0);
}

/**
 * custom_strcmp - Compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if the strings are equal, otherwise the difference
 * between the first
 * non-matching characters.
 */
int custom_strcmp(const char *s1, const char *s2)
{
while (*s1 && (*s1 == *s2))
{
s1++;
s2++;
}
return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

