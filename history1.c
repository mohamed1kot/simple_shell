#include "shell.h"

/**
 * _myhistory - prints the command history.
 *
 * @indormation: A pointer to the INFO struct that holds the command history.
 *
 * Return: Always returns 0.
*/

int _myhistory(INFO *indormation)
{
	print_list(indormation->history);
	return (0);
}

/**
 * get_history_file - Get the path to the history file.
 *
 * @indormation: A pointer to the INFO struct.
 *
 * Return: A dynamically allocated string containing the file path.
 *         Returns NULL on failure.
*/

char *get_history_file(INFO *indormation)
{
	char *buffer, *D;

	D = _getenv(indormation, "HOME=");
	if (!D)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(D) + _strlen(f_histroy) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, D);
	_strcat(buffer, "/");
	_strcat(buffer, f_histroy);
	return (buffer);
}

/**
 * write_history - Write command history to a file.
 *
 * @indormation: A pointer to the INFO struct.
 *
 * Return: 1 if successful, -1 on failure.
*/

int write_history(INFO *indormation)
{
	ssize_t fd;
	char *F_name = get_history_file(indormation);
	LSIT *Node = NULL;

	if (!F_name)
		return (-1);

	fd = open(F_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(F_name);
	if (fd == -1)
		return (-1);
	for (Node = indormation->history; Node; Node = Node->next)
	{
		_putsfd(Node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Read command history from a file.
 *
 * @indormation: A pointer to the INFO struct.
 *
 * Return: The number of history entries read, 0 on failure.
*/

int read_history(INFO *indormation)
{
	int i, end = 0, linecount = 0;
	ssize_t fd, length, size = 0;
	struct stat ST;
	char *buffer = NULL, *F_name = get_history_file(indormation);

	if (!F_name)
		return (0);

	fd = open(F_name, O_RDONLY);
	free(F_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &ST))
		size = ST.st_size;
	if (size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (0);
	length = read(fd, buffer, size);
	buffer[size] = 0;
	if (length <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(indormation, buffer + end, linecount++);
			end = i + 1;
		}
	if (end != i)
		build_history_list(indormation, buffer + end, linecount++);
	free(buffer);
	indormation->histcount = linecount;
	while (indormation->histcount-- >= M_history)
		delete_node_at_index(&(indormation->history), 0);
	renumber_history(indormation);
	return (indormation->histcount);
}
