#include "shell.h"


/**
 * node_starts_with - Find the first Node whose string
 * starts with a given prefix.
 *
 * @Node: A pointer to the head of the linked list.
 * @pre: The prefix to search for.
 * @c: A character to match at the start of the string,
 * or -1 to match any character.
 *
 * Return: A pointer to the first matching Node, or NULL if not found.
*/

LSIT *node_starts_with(LSIT *Node, char *pre, char c)
{
	char *ptr = NULL;

	while (Node)
	{
		ptr = starts_with(Node->str, pre);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (Node);
		Node = Node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a Node in a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @Node: A pointer to the Node whose index is to be found.
 *
 * Return: The index of the Node in the list, or -1 if not found.
*/

ssize_t get_node_index(LSIT *head, LSIT *Node)
{
	size_t j = 0;

	while (head)
	{
		if (head == Node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

/**
 * add_node - Add a new Node to the beginning of a linked list.
 *
 * @head: A pointer to a pointer to the head of the linked list.
 * @S: The string to be stored in the new Node (can be NULL).
 * @number: The numerical value to be stored in the new Node.
 *
 * Return: A pointer to the new Node if successful, NULL on failure.
*/

LSIT *add_node(LSIT **head, const char *S, int number)
{
	LSIT *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(LSIT));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(LSIT));
	new_head->num = number;
	if (S)
	{
		new_head->str = _strdup(S);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

