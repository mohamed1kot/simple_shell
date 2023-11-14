#include "shell.h"


/**
 * interactive - checks if the standard
 * nput is associated with a terminal or interactive device.
 *
 * @information : input struct.
 *
 * Return: If both conditions are met, it returns true;
 * otherwise, it returns false.
*/

int interactive(INFO *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

