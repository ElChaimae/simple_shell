#include "main.h"

/**
 * add_alias - Adds an alias to the alias list.
 * @name: alias name
 * @value: alias value
 * @alias_list: alias list
 * Return: nothing
 */
void add_alias(alias_t **alias_list, char *name, char *value)
{
alias_t *new_alias;	
new_alias = malloc(sizeof(alias_t));
if (new_alias == NULL)
{
write(STDERR_FILENO, "Error: failed to allocate memory for new alias.\n", 48);
return;
}
new_alias->name = strdup(name);
new_alias->value = strdup(value);
new_alias->next = *alias_list;   
*alias_list = new_alias;
}

/**
 * find_alias - Finds an alias in the alias list.
 * @name: alias name
 * @alias_list: alias list
 * Return: null
 */
alias_t *find_alias(alias_t *alias_list, char *name)
{
alias_t *alias_ptr;
for (alias_ptr = alias_list;
alias_ptr != NULL; alias_ptr = alias_ptr->next)
{
if (strcmp(name, alias_ptr->name) == 0)
{
return (alias_ptr);
}
}
return (NULL);
}

/**
 * delete_alias - Deletes an alias from the alias list.
 * @name: alias name
 * @alias_list: alias list
 * Return: nothing
 */
void delete_alias(alias_t **alias_list, char *name)
{
alias_t *alias_ptr;
alias_t *prev_ptr;
for (alias_ptr = *alias_list, prev_ptr = NULL;
alias_ptr != NULL;
prev_ptr = alias_ptr, alias_ptr = alias_ptr->next)
{
if (strcmp(name, alias_ptr->name) == 0)
{
if (prev_ptr == NULL)
{
*alias_list = alias_ptr->next;
}
else
{
prev_ptr->next = alias_ptr->next;
}
free(alias_ptr->name);
free(alias_ptr->value);
free(alias_ptr);
return;
}
}
}

