#include "shell.h"


/**
 * print_alias - Prints the alias stored in the given Node.
 *
 * @Node: A pointer to the Node containing the alias.
 *
 * Return: 0 on success, 1 on failure.
*/

int print_alias(LSIT *Node)
{
	char *ptr = NULL, *r = NULL;

	if (Node)
	{
		ptr = _strchr(Node->str, '=');
		for (r = Node->str; r <= ptr; r++)
			_putchar(*r);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * print_error - Print an error message.
 *
 * @information: A pointer to the INFO struct containing error information.
 * @e_str: The error message to print.
*/

void print_error(INFO *information, char *e_str)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(e_str);
}

/**
 * print_d - Print an integer to a file descriptor.
 *
 * @input: The integer to print.
 * @fd: The file descriptor to print to (STDOUT_FILENO or STDERR_FILENO).
 *
 * Return: The number of characters printed.
*/

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * print_list - Print the content of a linked list.
 *
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes printed.
*/

size_t print_list(const LSIT *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * print_list_str - Print the content of a linked list of strings.
 *
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes printed.
*/

size_t print_list_str(const LSIT *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

