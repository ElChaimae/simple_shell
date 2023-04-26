#include "main.h"

/**
 * is_exit - checks if a comman is exit
 * @command: command entered by the user
 * Return: 1 if the command entered by the user is
 * "exit", and 0 otherwise.
 */
int is_exit_command(char *command)
{
return strcmp(command, "exit") == 0;
}

/**
 * is_cd - function checks if the first token in the tokens
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
fprintf(stderr, "Error: %s\n", error_str);
}

