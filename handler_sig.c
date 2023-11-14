#include "shell.h"


/**
 * sig_Handler - Handle the SIGINT signal (Ctrl+C).
 *
 * @sigin_num: The signal number (unused).
*/

void sig_Handler(__attribute__((unused))int sigin_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
