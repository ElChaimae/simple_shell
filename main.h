#ifndef MAIN_H
#define MAIN_H

extern char **environ;
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int read_input(char **input_line, size_t *input_size);
int print_prompt(void);
char** tokenize(char *input);
int exec_cmd(char **args, int *pipefd);

#endif
