#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOK_SIZE 64

char **split_line(char *line);
char *read_line();
void free_string_array(char **array);
void print_string_array(char **array);
int simple_strcmp(char *a, char *b);
int cmd_cd(char **args);
void cmd_exit(char **args);
int start_process(char **args, char **envp);

#endif
