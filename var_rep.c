#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_INPUT_SIZE 1024

char *replace_variable(char *variable, int status);
char **parse_input(char *, int);

/**
 * replace_variable - replaces a single variable in a string
 * @variable: variable to replace (e.g. "$HOME")
 * @status: status of the previous command
 * Return: the value of the variable, or NULL if the variable is undefined
 */
char *replace_variable(char *variable, int status)
{
  char *value = NULL;

  if (strcmp(variable, "$$") == 0) {
    value = malloc(sizeof(char) * 20);
    sprintf(value, "%d", getpid());
  } else if (strcmp(variable, "$?") == 0) {
    value = malloc(sizeof(char) * 20);
    sprintf(value, "%d", WEXITSTATUS(status));
  } else if (strncmp(variable, "$", 1) == 0) {
    value = getenv(variable + 1);
  }

  return value;
}

/**
 * parse_input - parses user input into arguments and replaces variables
 * @input: user input
 * @status: status of the previous command
 * Return: a pointer to a list of strings containing the parsed arguments
 */
char **parse_input(char *input, int status)
{
  char **args = malloc(MAX_INPUT_SIZE / 2 + 1);
  char *token, *var_value;
  int i = 0;

  token = strtok(input, " \t\n");
  while (token != NULL) {
    var_value = replace_variable(token, status);
    if (var_value != NULL) {
      args[i++] = var_value;
    } else {
      args[i++] = token;
    }
    token = strtok(NULL, " \t\n");
  }
  args[i] = NULL;
  return args;
}

