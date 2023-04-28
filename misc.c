#include "main.h"
#include <unistd.h>

/**
 * is_exit_command - checks if a command is "exit"
 * @command: command entered by the user
 * Return: 1 if the command entered by the user is
 * "exit", and 0 otherwise.
 */
int is_exit_command(char *command)
{
return (strcmp(command, "exit") == 0);
}

/**
 * is_cd_command - function checks if the first token in the tokens
 * array is "cd
 * @tokens: tokens parsed from the user input
 * Return:1 if the first token in the array of tokens is
 * "cd", and 0 otherwise.
 */
int is_cd_command(char **tokens)
{
return (strcmp(tokens[0], "cd") == 0);
}

/*
 * print_error - Print an error message to stderr.
 * error_str: A string containing the error message.
 * Return: nothing
 */
void print_error(char *error_str)
{
write(STDERR_FILENO, "Error: ", 7);
write(STDERR_FILENO, error_str, strlen(error_str));
write(STDERR_FILENO, "\n", 1);
}

