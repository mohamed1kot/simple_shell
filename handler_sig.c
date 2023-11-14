#include "shell.h"


/**
 * sigintHandler - Handle the SIGINT signal (Ctrl+C).
 *
 * @sigin_num: The signal number (unused).
*/

void sigintHandler(__attribute__((unused))int sigin_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

