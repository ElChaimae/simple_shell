#include "main.h"

/**
 * exit_shell - Exits the shell.
 *
 * Return: Always returns -1.
 */
int exit_shell(void)
{
        write(STDOUT_FILENO, "Exiting Shell...\n", 17);
        return (-1);
}

