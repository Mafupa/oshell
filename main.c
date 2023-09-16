#include "main.h"

/**
 * split_line - splits a line in a list of arguments like in shell
 * @line: the line that we want to split
 * Return: a list of all the arguments
 */
char **split_line(char *line)
{
	int args_i = 0, q = 0, i = 0, j = 0, c = 0, len = 0;
	char **args;

	args = malloc(sizeof(char *) * TOK_SIZE);
	if (!args)
		return (NULL);
	while (line[len])
		len++;
	while (i <= len)
	{
		if (line[i] == '"' && q == 0)
		{
			q = 1;
			j = i + 1;
		}
		else if ((line[i] == '"' && q == 1) || (line[i] == ' ' && q == 0)\
				|| line[i] == '\n' || line[i] == '\0')
		{
			args[args_i] = malloc(sizeof(char) * (i - j + 1));
			if (!args)
				return (NULL);
			for (c = 0; c < (i - j); c++)
				args[args_i][c] = line[j + c];
			args[args_i][c] = '\0';
			args_i++;
			if (line[i] == ' ' && q == 0)
			{
				j = i + 1;
			}
			else
			{
				q = 0;
				i++;
				j = i;
			}
		}
		i++;
	}
	args[args_i] = NULL;
	return (args);
}


/**
 * free_string_array - free the memory allocated to a string array
 * @array: the string array (char **)
 */
void free_string_array(char **array)
{
	int i;

	if (!array)
		return;
	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * print_string_array - prints all the strings in an array
 * @array: the string array (char **)
 */
void print_string_array(char **array)
{
	int i;

	if (!array)
		return;
	for (i = 0; array[i]; i++)
		printf("[%s] ", array[i]);
	printf("\n");
}

/**
 * read_line - reads a line from the standart input and return it
 * Return: line from the standart input
 */
char *read_line()
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("no EOF");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	return (line);
}

/**
 * simple_strcmp - compares two strings
 * @a: first string
 * @b: second string
 * Return: 1 if they are the same, 0 if different
 */
int simple_strcmp(char *a, char *b)
{
	int i = 0;

	while (a[i] || b[i])
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}

/**
 * start_process - starts a process
 * @args: arguments given
 * Return: 1
 */
int start_process(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

int cmd_cd(char **args)
{
	if (chdir(args[1]) != 0)
		perror("hsh");
	return (1);
}

/**
 * main - oshell
 * @argc: argument count
 * @argv: argument vector
 * Return: EXIT_SUCCESS
 */
int main(int argc __attribute__ ((unused)), char **argv __attribute__ ((unused)))
{
	char *line;
	char **args;
	int status = 1;

	do {
		printf("($)");
		fflush(stdout);
		line = read_line();
		args = split_line(line);
		/*status = execute(args);*/
		if (strcmp(args[0], "exit") == 0)
			break;
		if (strcmp(args[0], "cd") == 0)
			status = cmd_cd(args);
		else
			status = start_process(args);
		
		/*status = strcmp(line, "exit\n");
		print_string_array(args);*/
		free(line);
		free_string_array(args);
	} while (status);
	return (EXIT_SUCCESS);
}
