#include "main.h"

/**
 * find_path - find a program's path in the PATH environement variable
 * @program_name: program's name
 * Return: the programs full path
 */
char *find_path(char *program_name, char **envp)
{
	int i = 0, j = 0, c, pn_len = 0;
	char *PATH, *attempt;

	PATH = custom_getenv("PATH", envp);
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
 * @envp: the environment vector
 * Return: the value of the environement valiable
 */
char *custom_getenv(char *name, char **envp)
{
	char **curr = envp;

	while(*curr)
	{
		printf("surge: %s\n", *curr);
		if (strcmp(*curr, name) == 0)
			return (*curr);
		curr++;
	}
	return (NULL);
}

/**
 * start_process - starts a process
 * @args: arguments given
 * Return: 1
 */
int start_process(char **args, char **envp)
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
	path = custom_getenv("PATH", envp);
	if (!path)
		printf("whyy");

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
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
