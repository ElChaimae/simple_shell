#include "main.h"

/**
 * free_tokens - Frees a double pointer array of strings
 * @tokens: Double pointer array of strings to free
 */
void free_tokens(char **tokens)
{
    size_t i;

    for (i = 0; tokens[i]; i++)
        free(tokens[i]);

    free(tokens);
}

/**
 * main - Simple Shell entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    char **tokens = NULL;
    size_t len = 0;
    ssize_t read = 0;

    do {
        printf("$ ");
        read = getline(&line, &len, stdin);

        if (read == -1)
            break;

        tokens = tokenize(line);
        if (tokens == NULL)
            continue;

        execute_command(tokens);

        free_tokens(tokens);
    } while (1);

    free(line);
    return (0);
}

