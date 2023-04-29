#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int run_command(char* input);
void free_args(char** args);
char** parse_args(char* input);
int main(int argc, char* argv[]);
int execute_command(char** args);

#endif /* MAIN_H_ */

