#include "main.h"

/**
 * alias_builtin - creates an alias for a command
 * @args: arguments to the "alias" command
 * @alias_list: pointer to the head of the alias list
 *
 * Return: always 0 (success)
 */
int alias_builtin(char **args, alias_t **alias_list)
{
alias_t *new_alias;
char *name = args[1], *value = args[2];

new_alias = malloc(sizeof(alias_t));
if (new_alias == NULL)
return (1);

new_alias->name = name;
new_alias->value = value;
new_alias->next = NULL;

add_alias(alias_list, name, value);

return (0);
}

