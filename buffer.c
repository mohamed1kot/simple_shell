#include "shell.h"


/**
 * input_buf - Read input from standard input into a buffer.
 *
 * @information: A pointer to the INFO struct.
 * @buffer: A pointer to the buffer for input.
 * @length: A pointer to the length of the buffer.
 *
 * Return: The number of characters read, -1 on failure.
*/

ssize_t input_buf(INFO *information, char **buffer, size_t *length)
{
	ssize_t l = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if U_getline
		l = getline(buffer, &len_p, stdin);
#else
		l = _getline(information, buffer, &len_p);
#endif
		if (l > 0)
		{
			if ((*buffer)[l - 1] == '\n')
			{
				(*buffer)[l - 1] = '\0';
				l--;
			}
			information->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(information, *buffer, information->histcount++);
			{
				*length = l;
				information->cmd_buf = buffer;
			}
		}
	}
	return (l);
}

/**
 * get_input - Get input from a buffer,
 * process it, and store it in the INFO struct.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: The number of characters processed, -1 on failure.
*/

ssize_t get_input(INFO *information)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t l = 0;
	char **buff_p = &(information->arg), *p;

	_putchar(BUF_FLUSH);
	l = input_buf(information, &buffer, &length);
	if (l == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i;

		check_chain(information, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			information->cmd_buf_type = C_NOR;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buffer;
	return (l);
}

/**
 * read_buf - Read data from a file descriptor into a buffer.
 *
 * @information: A pointer to the INFO struct.
 * @buffer: A pointer to the buffer for reading.
 * @i: A pointer to the current position in the buffer.
 *
 * Return: The number of bytes read, 0 on end of file, -1 on failure.
*/

ssize_t read_buf(INFO *information, char *buffer, size_t *i)
{
	ssize_t l = 0;

	if (*i)
		return (0);
	l = read(information->readfd, buffer, BUF_SIZE);
	if (l >= 0)
		*i = l;
	return (l);
}

