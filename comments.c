#include "main.h"
/**
 * remove_comment - Removes a comment from a command string.
 * @command: The command string.
 * Return: Nothing
 */
void remove_comment(char *command)
{
char *hash_pos = strchr(command, '#');
/* find the position of the '#' character in the command*/
if (hash_pos != NULL)
{
*hash_pos = '\0';
/*replace the '#' with a null character, effectively removing the comment*/
}
}

