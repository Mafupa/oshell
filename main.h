#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOK_SIZE 64

extern char **environ;

char **split_line(char *line);
char *read_line();
void free_string_array(char **array);
void print_string_array(char **array);
int simple_strcmp(char *a, char *b);
int cmd_cd(char **args);
void cmd_exit(char **args);
int cmd_env();
int start_process(char **args);
char *find_path(char *program_name);
char *custom_getenv(char *name);


#endif
