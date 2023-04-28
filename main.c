#include "main.h"
#define MAX_COMMAND_LENGTH 100


int execute_command(char *command);
/**
 * main - entry point for the program
 * @argc: the number of command-line arguments passed to the program
 * @argv: an array of strings containing the command-line arguments
 * Return: 0 on success
 */
int main() {
size_t command_len;
char command[MAX_COMMAND_LENGTH];
  
  while (1) {
        printf(">");
        fflush(stdout);
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;
        }
        command_len = strlen(command);
        if (command_len > 0 && command[command_len - 1] == '\n') {
            command[command_len - 1] = '\0';
        }
        execute_command(command);
    }
    return 0;
}

