#include "main.h"

int is_exit_command(char *command) {
    return strcmp(command, "exit") == 0;
}

int is_cd_command(char **tokens) {
    return strcmp(tokens[0], "cd") == 0;
}

/*
 * Print an error message to stderr.
 *
 * error_str: A string containing the error message.
 */
void print_error(char *error_str) {
    fprintf(stderr, "Error: %s\n", error_str);
}

