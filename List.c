#include "shell.h"


/**
 * list_len - Calculate the length of a linked list.
 *
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes in the list.
*/

size_t list_len(const LSIT *head)
{
	size_t l = 0;

	while (head)
	{
		head = head->next;
		l++;
	}
	return (l);
}

/**
 * LSITo_strings - Convert a linked list of strings to an array of strings.
 *
 * @head: A pointer to the head of the linked list.
 *
 * Return: A dynamically allocated array of strings,
 * terminated with a NULL pointer.Returns NULL on failure.
*/

char **LSITo_strings(LSIT *head)
{
	LSIT *Node = head;
	size_t l = list_len(head), j;
	char **strs;
	char *S;

	if (!head || !l)
		return (NULL);
	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);
	for (l = 0; Node; Node = Node->next, l++)
	{
		S = malloc(_strlen(Node->str) + 1);
		if (!S)
		{
			for (j = 0; j < l; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		S = _strcpy(S, Node->str);
		strs[l] = S;
	}
	strs[l] = NULL;
	return (strs);
}


