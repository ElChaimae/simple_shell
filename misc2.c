#include "main.h"

char* get_command_path(char *command) {
    char *path = get_path_value();
    char *full_path = allocate_full_path(path, command);
    free(path);
    return full_path;
}

void print_command_not_found(char *cmd) {
    printf("%s: command not found\n", cmd);
}

