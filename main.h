#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ARGS 512

int main();
void free_args(char** args);
char** parse_args(char* input);
int execute_command(char** args);
int run_command(char* input);
void write_stdout(const char* message, size_t len);
void write_stderr(const char* message, size_t len);

#endif

