#include "main.h"
/**
 * command_separator - executes multiple commands separated by semicolons.
 * @input: input entered by user
 * Return: 1 if any of the commands fail, and 0 otherwise.
 */
int command_separator(char *input)
{
char *saveptr;
char *token;
int child_status, status = 0;
char *args[3];

token = strtok_r(input, ";", &saveptr);
while (token != NULL)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(1);
}
else if (pid == 0) /* child process*/
{
args[0] = token;
args[1] = NULL;
execve(token, args, NULL);
perror("execve");
_exit(1); /*exit child process with error status*/
}
else /*parent process*/
{
waitpid(pid, &child_status, 0); /*wait for child to finish*/
if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
{
status = 1; /*set status to 1 if child process fails*/
}
}
token = strtok_r(NULL, ";", &saveptr); /* move to next token*/
}
return (status);
}
 
