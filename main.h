#ifndef MAIN_H
#define MAIN_H

#define MAX_INPUT_LENGTH 1024
#define TOKEN_BUFSIZE 64

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

/* struct for aliases */
typedef struct alias {
    char *name;
    char *value;
    struct alias *next;
} alias_t;

/* string functions */
char *_strdup(char *str);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);

/* token functions */
char **tokenize(char *input);
void free_tokens(char **tokens);

/* command functions */
int is_exit_command(char *command);
int is_cd_command(char **tokens);
int execute_command(char **args);
void execute_cd_command(char* dir);
char *get_command_path(char *command, char **envp);
void print_command_not_found(char *command);
void print_error(char *command);

/* alias functions */
alias_t *create_alias(char *name, char *value);
void add_alias(alias_t **alias_list, char *name, char *value);
void print_aliases(alias_t *alias_list);
alias_t *get_alias(alias_t *alias_list, char *name);
void free_aliases(alias_t **alias_list);

/*other functions*/
int execute_cmd(char **args);
void handle_sigint(int sig_num);
int exit_shell(char **args);


#endif /* MAIN_H */

