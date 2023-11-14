#include "shell.h"


/**
 * build_history_list - Add a history entry to the INFO struct.
 *
 * @information: A pointer to the INFO struct.
 * @buffer: The history entry to add.
 * @L_count: The line count for the history entry.
 *
 * Return: 0 on success.
*/

int build_history_list(INFO *information, char *buffer, int L_count)
{
	LSIT *Node = NULL;

	if (information->history)
		Node = information->history;
	add_Node_end(&Node, buffer, L_count);

	if (!information->history)
		information->history = Node;
	return (0);
}

/**
 * renumber_history - Renumber history entries in the INFO struct.
 *
 * @information: A pointer to the INFO struct.
 *
 * Return: The number of history entries.
*/

int renumber_history(INFO *information)
{
	LSIT *Node = information->history;
	int i = 0;

	while (Node)
	{
		Node->num = i++;
		Node = Node->next;
	}
	return (information->histcount = i);
}
