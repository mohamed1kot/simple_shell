#include "shell.h"


/**
 * _getline - Read a line of text from standard input and store it in a buffer.
 *
 * @information: A pointer to the INFO struct.
 * @pointer: A pointer to the buffer for storing the line.
 * @length: A pointer to the length of the line.
 *
 * Return: The number of characters read, -1 on failure.
*/

int _getline(INFO *information, char **pointer, size_t *length)
{
	static char buffer[BUF_SIZE];
	static size_t i, l;
	size_t t;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *pointer;
	if (ptr && length)
		s = *length;
	if (i == l)
		i = l = 0;

	r = read_buffer(information, buffer, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	t = c ? 1 + (unsigned int)(c - buffer) : l;
	new_ptr = _realloc(ptr, s, s ? s + t : t + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		_strncat(new_ptr, buffer + i, t - i);
	else
		_strncpy(new_ptr, buffer + i, t - i + 1);

	s += t - i;
	i = t;
	ptr = new_ptr;

	if (length)
		*length = s;
	*pointer = ptr;
	return (s);
}
