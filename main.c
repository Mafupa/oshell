#include "main.h"

/**
 * cmd_cd - change directory
 * @args: argument vector
 * Return: 1
 */
int cmd_cd(char **args)
{
	if (chdir(args[1]) != 0)
		perror("hsh");
	return (1);
}


/**
 * cmd_exit - exit the shell
 * @args: argument vector
 */
void cmd_exit(char **args)
{
	int status_code;

	if (!args)
		exit(EXIT_SUCCESS);
	if (!args[1])
		exit(EXIT_SUCCESS);
	status_code = atoi(args[1]);
	free_string_array(args);
	exit(status_code);
}

/**
 * cmd_env - prints the environement
 * Return: 1
 */
int cmd_env()
{
	char **env;

	for (env = environ; *env != NULL; env++)
		printf("%s\n",*env);
	return (1);
}


/**
 * main - oshell
 * @argc: argument count
 * @argv: argument vector
 * Return: EXIT_SUCCESS
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char *line;
	char **args;
	int status = 1;

	do {
		printf("($)");
		fflush(stdout);
		line = read_line();
		args = split_line(line);
		free(line);
		if (strcmp(args[0], "exit") == 0)
			cmd_exit(args);
		else if (strcmp(args[0], "cd") == 0)
			status = cmd_cd(args);
		else if (strcmp(args[0], "env") == 0)
			status = cmd_env();
		else if (strcmp(args[0], "") == 0)
			;
		else
			status = start_process(args);
		free_string_array(args);
	} while (status);
	return (EXIT_SUCCESS);
}
