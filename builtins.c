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
int cmd_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
		printf("%s\n", *env);
	return (1);
}

