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
		if (feof(stdin))
			return (-1);
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
	int write_result; 
	
	if(isatty(STDIN_FILENO))
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
			args = realloc(args, bufferSize * sizeof(char *));
		}
		token = strtok(NULL, " ");
		args[count++] = token;
	}
	return (args);
}


/**
 * exec_cmd - Execute a command with given arguments using execve.
 * @args: The arguments for the command to be executed.
 *
 * Return: On success, returns 0. On failure, returns -1.
 */
int exec_cmd(char **args)
{
	pid_t pid;
	int status;

	if (!*args || !args[0])
	{
		return (-1);
	}
	if (strcmp(args[0], "exit") == 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		return (-1);
	}
	else if (pid == 0)
	{
		execve(args[0], args, environ);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);

	return (0);
}
