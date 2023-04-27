#include "main.h"

/**
 *  execute_left_command - handles left pipe
 *  @args: arguments passed
 *  @pipefd: array for creating a pipe between two processes
 *  Return: 0
void execute_left_command(char **args, int pipefd[])
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
} 
else if (pid == 0)
{
/*Set up pipe*/
close(pipefd[0]);
dup2(pipefd[1], STDOUT_FILENO);
close(pipefd[1]);

/*Execute command*/
execute_child(args);
}
/* Close pipe write end*/
close(pipefd[1]);
/*Wait for child process to finish*/
wait_for_child(pid, &status);
}

/**
 * execute_right_command - handles right pipe
 * @args: arguments
 * @pipefd: array for creating a pipe between two processes
 * Return: nothing
 */
void execute_right_command(char **args, int pipefd[])
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/*Set up pipe*/
close(pipefd[1]);
dup2(pipefd[0], STDIN_FILENO);
close(pipefd[0]);
/*Execute command*/
execute_child(args);
}
/* Close pipe read end*/
close(pipefd[0]);
/* Wait for child process to finish*/
wait_for_child(pid, &status);
}

/**
 * check_for_pipe - checks if command is pipe
 * @args: arguments passed
 * Return: 0
 */
int check_for_pipe(char **args)
{
for (int i = 0; args[i] != NULL; i++)
{
if (strcmp(args[i], "|") == 0)
{
return (i);
}
}
return (-1);
}

/**
 * execute_single_command - executes a single command
 * @args: arguments passed
 * Return: nothing
 */
void execute_single_command(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/*Execute command*/
execute_child(args);
}
/*Wait for child process to finish*/
wait_for_child(pid, &status);
}

/**
 * execute_command - executes a command
 * @args: arguments passed
 * Return: 0
 */
 int execute_command(char **args)
{
int pipe_index = check_for_pipe(args);
if (pipe_index == -1)
{
/*No pipe found, execute single command*/
execute_single_command(args);
}
else
{
/*Pipe found, execute left and right commands*/
int pipefd[2];
if (pipe(pipefd) == -1)
{
perror("pipe");
return (0);
}
/ *Execute left command*/
args[pipe_index] = NULL;
execute_left_command(args, pipefd);
/*Execute right command*/
execute_right_command(&args[pipe_index+1], pipefd);
}
return (1);
}

