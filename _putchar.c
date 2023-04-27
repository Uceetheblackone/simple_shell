#include "sshell.h"

/**
 * _putchar - outputs the character c to stdout
 * @c: The character to be
 * outputted to the console
 * Return: returns 1 when successful.
 * returns -1 on error, and set "errno" accurately.
*/

int _putchar(char c)
{
	return write(1, &c, 1);
}
