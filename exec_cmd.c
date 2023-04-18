#include"main.h"

char* get_command_path(char *command);

/**
 * execute_cmd - Executes a command in a new process
 * @path: The full path of the executable file to execute
 * @tokens: array of strings containing the command and its args
 * return: 0 if successful, -1 if an error occurred
 */
int execute_cmd(char *path, char **tokens)
{
pid_t child_pid;
int status;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
return (-1);
}

if (child_pid == 0)
{
if (execve(path, tokens, NULL) == -1)
{
perror("execve");
_exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &status, 0);
}

return (0);
}

/**
 * execute_command - Executes a command given an array of tokens
 * @tokens: array of strings containing the command and its args
 * Return: 0 if successful, -1 if an error occurred
 */
int execute_command(char **tokens)
{
char *path;

if (is_exit_command(tokens[0]))
{
return (1);
}

if (is_cd_command(tokens))
{
return (execute_cd_command(tokens));
}

path = get_command_path(tokens[0]);

if (path == NULL)
{
print_command_not_found(tokens[0]);
return (-1);
}

if (execute_cmd(path, tokens) == -1)
{
free(path);
return (-1);
}

free(path);

return (0);
}

/**
 *
 */
int execute_cd_command(char **tokens) {
    char *new_dir;
    if (tokens[1] == NULL) {
        /*if no argument is provided, go to home directory*/
        new_dir = getenv("HOME");
    } else {
        new_dir = tokens[1];
    }
    if (chdir(new_dir) != 0) {
        /*if chdir() fails, print an error message*/
        print_error("cd");
        return 1;
    }
    return 0;
}


/**
 * get_path - Searches for an executable file in the directories
 * listed in the PATH environment variable.
 * @command: the name of the command to search for.
 * return: The full path of the executable file if found
 * or NULL if not found.
 */
char *get_path(char *command)
{
char *path_env = getenv("PATH");
char *path = NULL;
char *token;
char *path_copy;
struct stat st;

/*Make a copy of the PATH environment variable*/
/* to avoid modifying the original string*/
path_copy = strdup(path_env);

/*Get the first directory in the PATH*/
token = strtok(path_copy, ":");

/*Iterate over each directory in the PATH*/
while (token != NULL)
{
/*Construct the full path of the command by concatenating*/
/* the directory path and command name*/
path = malloc(strlen(token) + strlen(command) + 2);
strcpy(path, token);
strcat(path, "/");
strcat(path, command);

/*Check if the file exists and is executable*/
if (stat(path, &st) == 0 && st.st_mode & S_IXUSR)
{
free(path_copy);
return (path);
}

free(path);
/*Get the next directory in the PATH*/
token = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

/**
 * check_if_ls - Checks if the given command is "ls"
 * @cmd: The command to check
 * return: 1 if the command is "ls", 0 otherwise
 */
int check_if_ls(char *cmd)
{
if (strcmp(cmd, "ls") == 0)
{
return (1);
}
return (0);
}

