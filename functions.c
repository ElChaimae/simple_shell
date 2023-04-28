#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

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
    char *prompt_txt = "#cisfun$ ";
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
 * exec_cmd - Execute a command with given arguments using execvp.
 * @args: The arguments for the command to be executed.
 *
 * Return: On success, returns 0. On failure, returns -1.
 */
int exec_cmd(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error forking process");
        return (-1);
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* Parent process */
        do
        {
            if (waitpid(pid, &status, WUNTRACED) == -1)
            {
                perror("Error waiting for child process");
                return (-1);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (0);
}
