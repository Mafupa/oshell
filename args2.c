#include "main.h"

/**
 * remove_useless_space - removes useless space before and after command
 * @input: input filled with useless spaces
 * Return: input with no useless spaces
 */
char *remove_useless_space(char *input)
{
	char *result;
	size_t start = 0, end = strlen(input) - 1;

	while (input[start] && input[start] == ' ')
		start++;
	while (end > start && input[end] == ' ')
		end--;
	result = malloc(end - start + 2);
	strncpy(result, &input[start], end - start + 1);
	result[end - start + 1] = '\0';
	return (result);
}

/**
 * is_digits - check if all the characters of a string are digits
 * @str: the string
 * Return: 1 if they are all digits, 0 otherwise
 */
int is_digits(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '0')
			return (0);
	}
	return (1);
}
