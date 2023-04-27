#include "sshell.h"

/**
*_strcspn - function that returns the length of the
* initial segment of a string that does not contain
* any characters from a given set of characters 
* @str1: the first string
* @str2: the second string
* Return: returns that value as an unsigned
* integer of type size_t.
*/

size_t _strcspn(const char* str1, const char* str2)
{
	const char* p1 = str1;
	const char* p2;

	while (*p1)
	{
	p2 = str2;
	while (*p2)
	{
		if (*p1 == *p2)
		{
		return (size_t)(p1 - str1);
		}
		++p2;
	}
	++p1
	}

	return (size_t)(p1 - str1);
}
