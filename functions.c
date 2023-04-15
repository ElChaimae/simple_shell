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

token = strtok(input, " ");
args[count++] = token;

while (token != NULL)
{
if (count >= bufferSize)
{
bufferSize *= 2;
args = realloc(args, bufferSize *sizeof(char *));
}
token = strtok(NULL, " ");
args[count++] = token;
}
return (args);
}


/**
 * execute_command - Executes a command.
 * @full_path: The full path to the command.
 * @args: An array of arguments for the command.
 *
 * Return: 0 on success, -1 on failure.
 */
int exec_cmd(char **args)
{
extern char **environ;
pid_t pid;
int status;
char *full_path = (NULL);

if (!args || !*args || !**args) /* Check for valid command */
return (-1);

if (strcmp(args[0], "exit") == 0) /* Handle exit command */
return (exit_shell());

/* Find the full path of the command */
if (access(args[0], X_OK) == 0)
full_path = args[0];
else
full_path = find_command(args[0]);

if (!full_path)/* Execute the command */
return (-1);

pid = fork();
if (pid == -1)
{
perror("Fork error");
free(full_path);
return (-1);
}
else if (pid == 0)
{
execve(full_path, args, environ);
perror(full_path);
free(full_path);
exit(EXIT_FAILURE);
}
else
waitpid(pid, &status, 0);

free(full_path);

return (0);
}

