#ifndef MAIN_H
#define MAIN_H
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"
#define MAX_ARGS 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void wait_for_child(pid_t pid, int *status);
void handle_sigint(int sig);
int read_input(char **input_line, size_t *input_size);
int print_prompt(void);
char **tokenize(char *input);
void exec_cmd(const char **args);
int builtin_cd(char **args);
int builtin_help(char **args);
int builtin_exit(char **args);
int execute(char **args, char *const env[]);

#endif /* MAIN_H */

