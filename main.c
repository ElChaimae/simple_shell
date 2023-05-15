#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024

int run_command(char* input);

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    int status = 0;

    while (1) {
        if (isatty(fileno(stdin))) {
            write_stdout("$ ", 2);
            fflush(stdout);
        }

        if (getline(&input, &input_size, stdin) == -1)
            break;

        input[strcspn(input, "\n")] = '\0';

        status = run_command(input);

        if (isatty(fileno(stdin)) && status != 0) {
            write_stderr("\n", 1);
        }
    }

    free(input);
    return status;
}

