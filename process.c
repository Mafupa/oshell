/**
 * start_process - starts a process
 * @args: arguments given
 * Return: 1
 */
int start_process(char **args, char **envp)
{
	pid_t pid;
	int status;

	/*
	 * if (access(args[0], X_OK) == -1)
	 * {
	 * perror("hshd");
	 * return (1);
	 * }
	 */
	pid = fork();
	if (pid == 0)
	{
		/*if (execve(args[0], args, envp) == -1)*/
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
