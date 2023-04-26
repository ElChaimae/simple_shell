#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void print_env(char **args)
{
    int i = 0;
    while (environ[i]) {
        printf("%s\n", environ[i]);
        i++;
    }

    if (strcmp(args[0], "env") == 0) {
        printf("This is the env command\n");
    }
}

