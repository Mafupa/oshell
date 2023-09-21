#include "main.h"

/**
 * split_line - splits a line in a list of arguments like in shell
 * @a: the line that we want to split
 * Return: a list of all the arguments
 */
char **split_line(char *a)
{
	int args_i = 0, q = 0, i = 0, j = 0, c = 0, len = strlen(a);
	int args_len = TOK_SIZE;
	char **args = malloc(sizeof(char *) * TOK_SIZE);

	if (!args)
		return (NULL);
	while (i <= len)
	{
		if (a[i] == '"' && q == 0)
		{
			q = 1;
			j = i + 1;
		}
		else if ((a[i] == '"' && q) || (a[i] == ' ' && !q) || a[i] == '\n' || !a[i])
		{
			args[args_i] = malloc(sizeof(char) * (i - j + 1));
			if (!args[args_i])
			{
				free_string_array(args);
				return (NULL);
			}
			for (c = 0; c < (i - j); c++)
				args[args_i][c] = a[j + c];
			args[args_i][c] = '\0';
			args_i++;
			if (args_i >= args_len)
				args = realloc(args, sizeof(char *) * (args_len += TOK_SIZE));
			if (a[i] == ' ' && q == 0)
				j = i + 1;
			else
				q = 0;
			if (a[i] != ' ' || q != 1)
				j = ++i;
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
 * @stream: where we read the line from
 * Return: line from the standart input
 */
char *read_line(FILE *stream)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (custom_getline(&line, &bufsize, stream) == -1)
	{
		free(line);
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	return (line);
}


/**
 * custom_getline - get one line from the stream
 * @line: pointer to the line
 * @n: the expected size of the line
 * @stream: the stream
 * Return: the number of chars read, -1 if error
 */
ssize_t custom_getline(char **line, size_t *n, FILE *stream)
{
	size_t i = 0;
	int temp;

	if (!line || !n || !stream)
	{
		return (-1);
	}
	if (!(*line) || *n < TOK_SIZE)
	{
		*n = TOK_SIZE;
		*line = (char *)realloc(*line, *n);
		if (!(*line))
		{
			return (-1);
		}
	}
	while (1)
	{
		temp = fgetc(stream);
		if (temp == EOF || temp == '\n')
		{
			(*line)[i] = '\0';
			if (i == 0 && temp == EOF)
				return (-1);
			else
				return (i);
		}
		(*line)[i] = (char)temp;
		if (++i >= *n)
		{
			*n += TOK_SIZE;
			*line = (char *)realloc(*line, *n);
			if (!(*line))
			{
				return (-1);
			}
		}
	}
}
