#include "main.h"

char* replace_variables(char* buffer)
{
    char* token;
    char* variable;
    char* value;
    char* exit_status;
    char* result;
    size_t length;
    int status;

    token = strtok(buffer, "$");
    while (token != NULL)
    {
        variable = strtok(NULL, " \t\n\"\'|&;><$");
        if (variable != NULL)
        {
            if (strcmp(variable, "?") == 0)
            {
                exit_status = (char*)malloc(sizeof(char) * 4);
                if (exit_status == NULL)
                {
                    perror("malloc error");
                    return buffer;
                }
                sprintf(exit_status, "%d", WEXITSTATUS(status));
                length = strlen(token) + strlen(exit_status) + 1;
                value = (char*)malloc(sizeof(char) * length);
                if (value == NULL)
                {
                    perror("malloc error");
                    free(exit_status);
                    return buffer;
                }
                snprintf(value, length, "%s%s", token, exit_status);
                free(token);
                token = value;
                free(exit_status);
            }
        }
        result = strtok(NULL, "$");
        if (result != NULL)
        {
            length = strlen(token) + strlen(result) + 1;
            value = (char*)malloc(sizeof(char) * length);
            if (value == NULL)
            {
                perror("malloc error");
                return buffer;
            }
            snprintf(value, length, "%s%s", token, result);
            free(token);
            token = value;
        }
    }

    return token;
}

