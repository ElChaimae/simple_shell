#include "main.h"

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
write(STDERR_FILENO, " Exit..\n", 8);
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
char *prompt_txt = "shell$";
int write_result = write(STDOUT_FILENO, prompt_txt, strlen(prompt_txt));

if (write_result == -1)
{
perror("Error writing prompt to stdout");
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
int bufferSize = 10;
char **args = malloc(bufferSize * sizeof(char *));
char *token;
int count = 0;
char **temp;
token = strtok(input, " ");
args[count++] = token;

while (token != NULL)
{
if (count >= bufferSize)
{
bufferSize *= 2;
temp = realloc(args, bufferSize *sizeof(char *));
if (!temp)
{
perror("Error reallocating memory");
free(args);
return (NULL);
}
args = temp;
}
token = strtok(NULL, " ");
args[count++] = token;
}
return (args);
}

/**
 *  is_ls - checks if command is bin/ls
 *  @command - command entered by user
 *  Return: 1 on success
 */
int is_ls(char *command)
{
char *ls = "/bin/ls";
int i;

for (i = 0; command[i] && ls[i]; i++)
{
if (command[i] != ls[i])
return (0);
}

return (command[i] == '\0' && ls[i] == '\0');
}

