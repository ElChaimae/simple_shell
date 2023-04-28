#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "main.h"

#define MAX_ARGS 100

/**
 * main - Entry point.
 * @argc: The number of arguments passed.
 * @argv: An array of pointers to the arguments.
 * @env: An array of pointers to the environment variables.
 *
 * Return: 0 on success, 1 otherwise.
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **env)
{
    char **args, *error_message;
    int ret;
    size_t n = 0;
    ssize_t nread;
    int i = 0;
    char *line, *token;
    signal(SIGINT, SIG_IGN);

    while (1)
    {
        line = NULL;
        nread = getline(&line, &n, stdin);
        if (nread == -1) {
            free(line);
            continue;
        }
        if (strcmp(line, "\n") == 0) {
            free(line);
            continue;
        }
        args = malloc(sizeof(char *) * MAX_ARGS);
        if (!args) {
            free(line);
            continue;
        }
        token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = strdup(token);
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        free(line);
        if (i == 0) {
            free(args);
            continue;
        }

        errno = 0;  /* Clear any previous error*/
        ret = execute(args, env);
        free(args);

        if (ret != EXIT_SUCCESS)
        {
            error_message = strerror(errno);
            fprintf(stderr, "%s\n", error_message);
            if (errno == ENOMEM) {
                exit(EXIT_FAILURE);
            }
        }
    }
    return EXIT_SUCCESS;
}

