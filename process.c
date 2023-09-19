#include "main.h"

/**
 * find_path - find a program's path in the PATH environement variable
 * @program_name: program's name
 * Return: the programs full path
 */
char *find_path(char *program_name)
{
	int i = 0, j = 0, c, pn_len = 0;
	char *PATH, *attempt;

	PATH = custom_getenv("PATH");
	if (!PATH)
		return (NULL);
	while (program_name[pn_len])
		pn_len++;
	printf("bef");
	fflush(stdout);
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] != ':')
			continue;
		attempt = malloc(sizeof(char) * (i - j + 1));
		if (!attempt)
			return (NULL);
		for (c = 0; c < (i - j); c++)
		{
			attempt[c] = PATH[j + c];
		}
		attempt[c] = '\0';
		j = i;
		printf("attempt: %s\n", attempt);
	}
	return (attempt);
}



/*
 * custom_getenv - get a environement variable
 * @name: the environement variable's title
 * Return: the value of the environement valiable
 */
char *custom_getenv(char *name)
{
	int name_len = 0;
	char **env;

	if (!name || !environ)
		return (NULL);
	while (name[name_len])
		name_len++;
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (&(*env)[name_len + 1]);
	}
	return (NULL);
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
	char *path;

	/*
	 * if (access(args[0], X_OK) == -1)
	 * {
	 * perror("hshd");
	 * return (1);
	 * }
	 */
	path = find_path(args[0]);
	if (!path)
		printf("why\n");

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
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
