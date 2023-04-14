#include "main.h"

/**
 * main - entry point for the program
 * @argc: the number of command-line arguments passed to the program
 * @argv: an array of strings containing the command-line arguments
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char *input = NULL;
	size_t input_size = 0;
	char **args = NULL;

	while (1)
	{
		print_prompt();
		read_input(&input, &input_size);
		input[strcspn(input, "\n")] = '\0';
		args = tokenize(input);
		exec_cmd(args);
	}
	free(input);

	return (0);
}
