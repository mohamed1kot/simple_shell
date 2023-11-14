#include "shell.h"


/**
 * add_node_end - Add a new Node to the end of a linked list.
 *
 * @head: A pointer to a pointer to the head of the linked list.
 * @str: The string to be stored in the new Node (can be NULL).
 * @number: The numerical value to be stored in the new Node.
 *
 * Return: A pointer to the new Node if successful, NULL on failure.
*/

LSIT *add_node_end(LSIT **head, const char *str, int number)
{
	LSIT *N_node, *Node;

	if (!head)
		return (NULL);

	Node = *head;
	N_node = malloc(sizeof(LSIT));
	if (!N_node)
		return (NULL);
	_memset((void *)N_node, 0, sizeof(LSIT));
	N_node->num = number;
	if (str)
	{
		N_node->str = _strdup(str);
		if (!N_node->str)
		{
			free(N_node);
			return (NULL);
		}
	}
	if (Node)
	{
		while (Node->next)
			Node = Node->next;
		Node->next = N_node;
	}
	else
		*head = N_node;
	return (N_node);
}

/**
 * delete_node_at_index - Delete a Node at a specified idx in a linked list.
 *
 * @head: A pointer to a pointer to the head of the linked list.
 * @idx: The idx of the Node to be deleted.
 *
 * Return: 1 if the Node is deleted successfully,
 * 0 if the Node is not found or head is NULL.
*/

int delete_node_at_index(LSIT **head, unsigned int idx)
{
	LSIT *Node, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		Node = *head;
		*head = (*head)->next;
		free(Node->str);
		free(Node);
		return (1);
	}
	Node = *head;
	while (Node)
	{
		if (i == idx)
		{
			previous_node->next = Node->next;
			free(Node->str);
			free(Node);
			return (1);
		}
		i++;
		previous_node = Node;
		Node = Node->next;
	}
	return (0);
}

/**
 * free_list - Free the memory used by
 * a linked list and set the head pointer to NULL.
 *
 * @head_P: A pointer to a pointer to the head of the linked list.
*/

void free_list(LSIT **head_P)
{
	LSIT *Node, *next_node, *head;

	if (!head_P || !*head_P)
		return;
	head = *head_P;
	Node = head;
	while (Node)
	{
		next_node = Node->next;
		free(Node->str);
		free(Node);
		Node = next_node;
	}
	*head_P = NULL;
}

