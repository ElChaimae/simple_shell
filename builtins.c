#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define MAX_INPUT_SIZE 1024

int handle_built_in_commands(char **);
void print_process_info(int, int);

/**
 * handle_built_in_commands - handles built-in commands
 * @args: arguments
 * Return: 0
 */
int handle_built_in_commands(char **args)
{
    if (args[0] == NULL)
    {
        return (0);
    }
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        return (cd(args));
    }
    return (-1);
}


/**
 * print_process_info - prints process and exit status
 * @pid: process ID
 * @status: exit status
 * Return: nothing
 */
void print_process_info(int pid, int status)
{
char pid_str[20], status_str[20];

sprintf(pid_str, "$$: %d\n", pid);
write(STDOUT_FILENO, pid_str, strlen(pid_str));
sprintf(status_str, "$?: %d\n", status);
write(STDOUT_FILENO, status_str, strlen(status_str));
}
