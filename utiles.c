#include "shell.h"

/**
 * convert_number - Convert a number to a specified base and apply flag.
 *
 * @number: The number to convert.
 * @base: The base to convert the number to (e.g., 10 for decimal).
 * @flag: Flags for conversion (e.g., lower/uppercase hex).
 *
 * Return: A string containing the converted number.
*/

char *convert_number(long int number, int base, int flag)
{
	static char *arr;
	static char buffer[50];
	char sig = 0;
	char *Ptr;
	unsigned long n = number;

	if (!(flag & conv_unsign) && number < 0)
	{
		n = -number;
		sig = '-';

	}
	arr = flag & conv_lower ? "0123456789abcdef" : "0123456789ABCDEF";
	Ptr = &buffer[49];
	*Ptr = '\0';

	do	{
		*--Ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sig)
		*--Ptr = sig;
	return (Ptr);
}

/**
 * set_info - Set information in the INFO struct.
 *
 * @information: A pointer to the INFO struct.
 * @av: An arr of strings containing command line arguments.
*/

void set_info(INFO *information, char **av)
{
	int j = 0;

	information->fname = av[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (j = 0; information->argv && information->argv[j]; j++)
			;
		information->argc = j;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * hsh - Main function for the shell program.
 *
 * @information: A pointer to the INFO struct.
 * @av: An arr of strings representing the command-line arguments.
 *
 * Return: The exit status of the shell.
*/

int hsh(INFO *information, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(information);
		if (r != -1)
		{
			set_info(information, av);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_ret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_ret);
}

/**
 * starts_with - Check if a string starts with a specified prefix.
 *
 * @stack: The string to check.
 * @needle: The prefix to check for at the beginning of stack.
 *
 * Return: A pointer to the first character in
 * stack after the prefix if found, or NULL if not found.
*/

char *starts_with(const char *stack, const char *needle)
{
	while (*needle)
		if (*needle++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * replace_vars - Replace environment variables
 * and special variables in command arguments.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: 0 if successful, -1 on failure.
*/

int replace_vars(INFO *information)
{
	int j = 0;
	LSIT *Node;

	for (j = 0; information->argv[j]; j++)
	{
		if (information->argv[j][0] != '$' || !information->argv[j][1])
			continue;

		if (!_strcmp(information->argv[j], "$?"))
		{
			replace_string(&(information->argv[j]),
				_strdup(convert_number(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[j], "$$"))
		{
			replace_string(&(information->argv[j]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		Node = node_starts_with(information->env, &information->argv[j][1], '=');
		if (Node)
		{
			replace_string(&(information->argv[j]),
				_strdup(_strchr(Node->str, '=') + 1));
			continue;
		}
		replace_string(&information->argv[j], _strdup(""));

	}
	return (0);
}

