#include "shell.h"


/**
 * _realloc - Reallocate memory for a previously allocated pointer.
 *
 * @pointer: A pointer to the previously allocated memory.
 * @o_size: The size of the old memory block.
 * @N_size: The size of the new memory block.
 *
 * Return: A pointer to the reallocated memory if successful, NULL on failure.
*/

void *_realloc(void *pointer, unsigned int o_size, unsigned int N_size)
{
	char *P;

	if (!pointer)
		return (malloc(N_size));
	if (!N_size)
		return (free(pointer), NULL);
	if (N_size == o_size)
		return (pointer);

	P = malloc(N_size);
	if (!P)
		return (NULL);

	o_size = o_size < N_size ? o_size : N_size;
	while (o_size--)
		P[o_size] = ((char *)pointer)[o_size];
	free(pointer);
	return (P);
}
