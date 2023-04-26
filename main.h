#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/stat.h>

/* Function prototypes */
char* get_command_path(char *command);
char *_getenv(const char *name);
void print_error(char *error_str);
int execute_cd_command(char **tokens);
int execute_command(char **tokens);
int read_input(char **input_line, size_t *input_size);
int print_prompt(void);
char **tokenize(char *input);
char *find_command(char *cmd);
char *get_path_value(void);
int exit_shell(void);
char *allocate_full_path(char *path, char *cmd);
int find_in_directory(char *dir, char *cmd, char *full_path);
void print_env(char **args);
char *get_path(char *command);
int check_if_ls(char *cmd);
int is_exit_command(char *cmd);
int is_cd_command(char **tokens);
void print_command_not_found(char *cmd);

#endif /* MAIN_H */

