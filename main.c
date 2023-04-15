#include "main.h"

int main(void)
{
    char *input_line = NULL;
    size_t input_size = 0;
    int status;
char **args = tokenize(input_line);

    while (1)
    {
        /* Print the prompt and read input */
        status = print_prompt();
        if (status == -1)
            continue;

        status = read_input(&input_line, &input_size);
        if (status == -1)
            continue;

        /* Execute the command */
        exec_cmd(args);

        /* Free memory */
        free(args);
        free(input_line);
    }

    return (0);
}

