#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_ENV_VARS 1000

/**
 * find_env_var - Finds the index of the environment variable
 * @name: name of environment variable
 * @envp: Parameter containing environment variables
 * Return: 0 on success, otherwise -1
 */
int find_env_var(char *name, char **envp)
{
int i;

for (i = 0; envp[i] != NULL; i++)
{
if (strncmp(name, envp[i], strlen(name)) == 0)
{
return (i);
}
}
return (-1);
}

/**
 * split_env_var - splits the environment variable into name and value
 * @env_var: environment variable
 * @env_var_name: name of environment variable
 * @env_var_value: value of environment variable
 * Return: nothing
 */
void split_env_var(char *env_var, char **env_var_name, char **env_var_value)
{
int i;

for (i = 0; env_var[i] != '\0'; i++)
{
if (env_var[i] == '=')
{
*env_var_name = malloc(i + 1);
strncpy(*env_var_name, env_var, i);
(*env_var_name)[i] = '\0';
*env_var_value = strdup(&env_var[i + 1]);
return;
}
}
*env_var_name = NULL;
*env_var_value = NULL;
}

/**
 * shell_env - Prints all environment variables
 * @envp:Parameter containing environment variables
 * Return: 1 on success
 */
int shell_env(char **envp)
{
int i;

for (i = 0; envp[i] != NULL; i++)
{
write(STDOUT_FILENO, envp[i], strlen(envp[i]));
write(STDOUT_FILENO, "\n", 1);
}
return (1);
}

/**
 * shell_setenv - Set an environment variable
 * @args: arguments to be passed
 * @envp: Parameter containing environment variables
 * Return: 1 on success
 */
int shell_setenv(char **args, char **envp)
{
char *name, *value, *env_var_name, *env_var_value, *new_env_var;
int index;

if (args[1] == NULL)
{
write(STDOUT_FILENO, "Usage: setenv NAME [VALUE]\n", 27);
return (1);
}
name = args[1];
if (args[2] != NULL)
{
value = args[2];
}
else
{
value = "";
}
index = find_env_var(name, envp);
if (index >= 0)
{
split_env_var(envp[index], &env_var_name, &env_var_value);
free(envp[index]);
new_env_var = malloc(strlen(name) + strlen(value) + 2);
sprintf(new_env_var, "%s=%s", name, value);
envp[index] = new_env_var;
}
else
{
if (index >= MAX_ENV_VARS)
{
write(STDOUT_FILENO, "Too many environment variables\n", 32);
return (1);
}
new_env_var = malloc(strlen(name) + strlen(value) + 2);
sprintf(new_env_var, "%s=%s", name, value);
envp[index + 1] = NULL;
envp[index] = new_env_var;
}
return (1);
}

