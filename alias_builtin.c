#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


alias_t* find_alias(alias_t** alias_list, const char* name) {
    alias_t* current = *alias_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_alias(alias_t **alias_list, char *name, char *value) {
    alias_t *new_alias = malloc(sizeof(alias_t));
    if (new_alias == NULL) {
        fprintf(stderr, "Failed to allocate memory for new alias\n");
        return;
    }

    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = NULL;

    if (*alias_list == NULL) {
        *alias_list = new_alias;
    } else {
        alias_t *current = *alias_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_alias;
    }
}

/**
 * alias_builtin - creates an alias for a command
 * @args: arguments to the "alias" command
 * @alias_list: pointer to the head of the alias list
 *
 * Return: always 0 (success)
 */
int alias_builtin(char **args, alias_t **alias_list) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Usage: alias NAME VALUE\n");
        return 1;
    }

    add_alias(alias_list, args[1], args[2]);

    return 0;
}

