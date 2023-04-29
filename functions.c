#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"
#define READ_END 0
#define WRITE_END 1

/**
 * read_input - Reads a line of input from stdin and stores it in memory.
 * @input_line: Pointer to a pointer to a character
 * @input_size: Pointer to a size_t
 *
 * Return: On success, 0. On failure, -1.
 */
int read_input(char **input_line, size_t *input_size)
{
    ssize_t read_result = getline(input_line, input_size, stdin);

    if (read_result == -1)
    {
        if (feof(stdin))
            return (-1);
        perror("Error reading input");
        exit(EXIT_FAILURE);
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
    char *prompt_txt = "$ ";
    ssize_t write_result;

    if (isatty(STDOUT_FILENO))
    {
        write_result = write(STDOUT_FILENO, prompt_txt, strlen(prompt_txt));
        if (write_result == -1)
        {
            perror("Error writing prompt to stdout");
            return (-1);
        }
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
    int bufsize = TOKEN_BUFSIZE;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;
    int pos = 0;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[pos] = strdup(token);
        pos++;

        if (pos >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }

    tokens[pos] = NULL;
    return tokens;
}


/**
 * exec_cmd - execute the command with arguments
 * @args: the list of arguments for the command
 * @pipefd: the file descriptors for the pipe
 * Return: 0 on success, -1 on failure
 */
int exec_cmd(char **args, int pipefd[])
{
    int pid, status;

    if (!args || !*args)
        return -1;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }

    if (pid == 0)
    {
        if (pipefd[READ_END] != -1)
        {
            close(STDIN_FILENO);
            dup(pipefd[READ_END]);
            close(pipefd[READ_END]);
        }

        if (pipefd[WRITE_END] != -1)
        {
            close(STDOUT_FILENO);
            dup(pipefd[WRITE_END]);
            close(pipefd[WRITE_END]);
        }

        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return -1;
        }
        return 0;
    }
    return 0;
}

