#include "shell.h"

/**
 * _itos - converts an integer into a string
 * @n: integer to be converted
 *
 * Return: the converted string
 */
char *_itos(int n)
{
	char *buf = malloc(12);
	char *ptr = buf;
	int is_min = FALSE;
	int nmask = 1000000000;
	int d = 0;

	if (n == INT_MIN)
	{
		*ptr = '-';
		ptr++;
		n = INT_MAX;
		is_min = TRUE;
	}

	if (n < 0)
	{
		*ptr = '-';
		ptr++;
		n = -n;
	}

	while (nmask > 9 && d == 0)
	{
		d = n / nmask;
		n %= nmask;
		nmask /= 10;
	}

	if (d != 0)
	{
		*ptr = d + '0';
		ptr++;
	}

	while (nmask > 9)
	{
		d = n / nmask;
		*ptr = d + '0';
		ptr++;
		n %= nmask;
		nmask /= 10;
	}

	if (is_min == TRUE)
		n += 1;

	*ptr = n + '0';
	ptr++;
	*ptr = '\0';
	return (buf);
}

/**
 * _stoi - converts a string into a integer
 * @s: string to be converted
 *
 * Return: the converted integer
 */
int _stoi(char *s)
{
	int n = 0;
	int sign = 1;
	int s_int;

	if (*s == '=' && *(s + 1) >= '0' && *(s + 1) <= '9')
	{
		sign = -1;
		s++;
	}

	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			s_int = *s - 48;
			if (sign == 1)
				n = (n * 10) + s_int;
			else
				n = (n * 10) - s_int;
		}
		else
			return (-1);
		s++;
	}

	return (n);
}
