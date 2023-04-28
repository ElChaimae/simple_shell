#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * read_input - Reads a line of input from stdin and stores it in memory.
 * @input_line: Pointer to a pointer to a character
 * @input_size: Pointer to a size_t
 *
 * Return: On success, 0. On failure, -1.
 */
int read_input(char **input_line, size_t *input_size)
{
    int read_result = getline(input_line, input_size, stdin);

    if (read_result == -1)
    {
        write(STDERR_FILENO, "\n", 1);
        exit(EXIT_SUCCESS);
    }
    return (0);
}

/**
 * print_prompt - Writes a prompt string to stdout.
 *
 * Return: On success, returns 0. On failure, returns -1.
 */
int print_prompt(void)
{
    char *prompt_txt = "shell$ ";
    int write_result = write(STDOUT_FILENO, prompt_txt, strlen(prompt_txt));

    if (write_result == -1)
    {
        char *error_msg = "Error writing prompt to stdout\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        return (-1);
    }
    return (0);
}

/**
 * tokenize - splits a string into an array of tokens separated by whitespace
 * @input: the string to tokenize
 *
 * Return: an array of strings representing the tokens in the input string
 */
char **tokenize(char *input)
{
    const char *delimiter = " \t\n\r\'\"`\\*&#";
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    char *token;
    int i = 0;

    if (args == NULL)
        return (NULL);

    token = strtok(input, delimiter);
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        token = strtok(NULL, delimiter);
        i++;
    }
    args[i] = NULL;

    return (args);
}

/**
 * builtin_cd - changes the current working directory of the process
 * @args: an array of arguments passed to the cd command
 *
 * Return: always returns 0
 */
int builtin_cd(char **args)
{
    if (args[1] == NULL)
    {
        char *error_msg = "Error: expected argument to \"cd\"\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
    return (0);
}

/**
 * builtin_help - displays help information for the shell
 * @args: an array of arguments passed to the help command
 *
 * Return: always returns 0
 */
int builtin_help(char **args __attribute__((unused)))
{
    char *help_str = "Simple Shell\n"
                     "Type program names and arguments, and hit enter.\n"
                     "The following are built in:\n"
                     "  cd\n"
                     "  help\n"
                     "  exit\n"
                     "Use the man command for information on other programs.\n";
    int write_result = write(STDOUT_FILENO, help_str, strlen(help_str));

    if (write_result == -1)
    {
        perror("Error writing help to stdout");
        return (-1);
    }
    return (0);
}

