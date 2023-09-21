#include "main.h"

/**
 * cmd_cd - change directory
 * @args: argument vector
 * @prgm_name: program's name
 * Return: 1
 */
int cmd_cd(char **args, char *prgm_name)
{
	if (chdir(args[1]) != 0)
		perror(prgm_name);
	return (1);
}


/**
 * cmd_exit - exit the shell
 * @args: argument vector
 * @prgm: program's name
 */
void cmd_exit(char **args, char *prgm)
{
	int sc;

	if (!args)
		exit(EXIT_SUCCESS);
	if (!args[1])
		exit(EXIT_SUCCESS);
	if (is_digits(args[1]) == 0)
	{
		fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", prgm, args[1]);
		free_string_array(args);
		exit(2);
	}
	sc = atoi(args[1]);
	if (sc < 0)
	{
		fprintf(stderr, "%s: 1: exit: Illegal number: %d\n", prgm, sc);
		free_string_array(args);
		exit(2);
	}
	exit(sc);
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

