#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* function prototypes */
int read_input(char **input_line, size_t *input_size);
int print_prompt(void);
char **tokenize(char *input);
int exec_cmd(char **args);
char *find_command(char *cmd);
int exit_shell(void);
char *get_path(void);
char *allocate_full_path(char *path, char *cmd);
int find_in_directory(char *dir, char *cmd, char *full_path);
void print_env(char **args);
char *_getenv(const char *name);

#endif /* MAIN_H */

