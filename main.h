#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 512
#define BUFFER_SIZE 1024

/**
 * struct alias - struct for alias
 * @name: The name of the alias
 * @value: The value of the alias
 * @next: next alias
 */
typedef struct alias
{
char *name;
char *value;
struct alias *next;
} alias_t;

int main(void);
void free_args(char **args);
char *find_command(char *cmd, char *command_path);
char **parse_args(char *input);
int execute_command(char **args);
int run_command(char *input, alias_t **alias_list);
void write_stdout(const char *message, size_t len);
void write_stderr(const char *message, size_t len);
void add_alias(alias_t **alias_list, char *name, char *value);
int alias_builtin(char **args, alias_t **alias_list);
alias_t *find_alias(alias_t **alias_list, const char *name);
void cd_builtin(char **args);
int command_separator(char *input);
void env_builtin(char **envp);
void exit_builtin(char **args, int *status);
char *my_getline(int fd);
void delete_alias(alias_t **alias_list, char *name);
int cd(char **args);
void remove_comment(char *command);
int find_env_var(char *name, char **envp);
void split_env_var(char *env_var, char **env_var_name, char **env_var_value);
int shell_env(char **envp);
int shell_setenv(char **args, char **envp);
long str_to_long(char *str);
char *get_path_value(void);
char *allocate_full_path(char *path, char *cmd);
int find_in_directory(char *dir, char *cmd, char *full_path);
int logical_operators(char *input);
int is_exit_command(char *command);
int is_cd_command(char **tokens);
void print_error(char *error_str);
char *get_path(char *command, char **envp);
char **parse_input(char *input);
int handle_built_in_commands(char **args);
void print_process_info(int pid, int status);
char *replace_variables(char *buffer);
char *get_variable_value(char *variable);

#endif /* MAIN_H */

