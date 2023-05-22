#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_ENV_VARS 1000

/**
 * find_env_var - Finds the index of the environment variable
 * @name: name of environment variable
 * @envp: Parameter containing environment variables
 * Return: Index of the environment variable on success, otherwise -1
 */
int find_env_var(char *name, char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(name, envp[i], strlen(name)) == 0)
        {
            return i;
        }
    }
    return -1;
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
    int len = strlen(env_var);
    for (i = 0; i < len; i++)
    {
        if (env_var[i] == '=')
        {
            *env_var_name = malloc(i + 1);
            if (*env_var_name == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for environment variable name\n");
                exit(EXIT_FAILURE);
            }
            strncpy(*env_var_name, env_var, i);
            (*env_var_name)[i] = '\0';
            *env_var_value = strdup(&env_var[i + 1]);
            if (*env_var_value == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for environment variable value\n");
                exit(EXIT_FAILURE);
            }
            return;
        }
    }
    *env_var_name = NULL;
    *env_var_value = NULL;
}

/**
 * shell_env - Prints all environment variables
 * @envp: Parameter containing environment variables
 * Return: 1 on success
 */
int shell_env(char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++)
    {
        if (write(STDOUT_FILENO, envp[i], strlen(envp[i])) == -1)
        {
            fprintf(stderr, "Failed to write environment variable\n");
            exit(EXIT_FAILURE);
        }
        if (write(STDOUT_FILENO, "\n", 1) == -1)
        {
            fprintf(stderr, "Failed to write newline character\n");
            exit(EXIT_FAILURE);
        }
    }
    return 1;
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
        if (write(STDERR_FILENO, "Usage: setenv NAME [VALUE]\n", 27) == -1)
        {
            fprintf(stderr, "Failed to write usage message\n");
            exit(EXIT_FAILURE);
        }
        return 1;
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
    if (index != -1)
    {
        split_env_var(envp[index], &env_var_name, &env_var_value);
        free(envp[index]);
        new_env_var = malloc(strlen(env_var_name) + strlen(value) + 2);  /*+2 for '=' and null terminator*/
        if (new_env_var == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for new environment variable\n");
            exit(EXIT_FAILURE);
        }
        sprintf(new_env_var, "%s=%s", env_var_name, value);
        envp[index] = new_env_var;
        free(env_var_name);
        free(env_var_value);
    }
    else
    {
        new_env_var = malloc(strlen(name) + strlen(value) + 2);  /*+2 for '=' and null terminator*/
        if (new_env_var == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for new environment variable\n");
            exit(EXIT_FAILURE);
        }
        sprintf(new_env_var, "%s=%s", name, value);
        for (index = 0; envp[index] != NULL; index++)
        {
            if (index >= MAX_ENV_VARS)
            {
                fprintf(stderr, "Maximum number of environment variables reached\n");
                exit(EXIT_FAILURE);
            }
        }
        envp[index] = new_env_var;
        envp[index + 1] = NULL;
    }

    return 1;
}



/**
 * shell_unsetenv - Unset an environment variable
 * @args: arguments to be passed
 * @envp: Parameter containing environment variables
 * Return: 1 on success
 */
int shell_unsetenv(char **args, char **envp)
{
    char *name;
    int i, j;

    if (args[1] == NULL)
    {
        if (write(STDERR_FILENO, "Usage: unsetenv NAME\n", 22) == -1)
        {
            fprintf(stderr, "Failed to write usage message\n");
            exit(EXIT_FAILURE);
        }
        return 1;
    }

    name = args[1];

    for (i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(name, envp[i], strlen(name)) == 0)
        {
            free(envp[i]);
            for (j = i; envp[j] != NULL; j++)
            {
                envp[j] = envp[j + 1];
            }
            break;
        }
    }

    return 1;
}

