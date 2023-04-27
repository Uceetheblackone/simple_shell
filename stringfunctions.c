#include "shell.h"

/**
 * _strlen - functions that returns string length.
 * @str: input value
 *
 * Return: Determine the number of characters in the string
 * and return it as an integer
*/
int _strlen(char *str)
{
	int index;

	if (!str)
	return (0);

	for (index = 0; str[index] != '\0'; index++)

	return (index);
}

/**
 * _strcmp - Compares two strings based on their
 * alphabetical order and returns the result
 * @str1: displays the first string
 * @str2: displays the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
*/
int _strcmp(char *str1, char *str2)
{
	int index = 0;

	while (str1[index] == str2[index] && str1[index] != '\0' && str2[index] != '\0')
	{
	index++;
	}

	if (str1[index] == '\0' && str2[index] == '\0')
	{
	return (0);
	}
	else
	{
	return str1[index] - str2[index];
	}
}
/**
 * _strcat - Joins together two strings into a single string
 * @dest: the memory location where
 * the resulting data will be stored
 * @src: the memory location of source data
 *
 * Return: pointer to where the resulting
 * data is stored.
 */
char *_strcat(char *dest, char *src)
{
	char *a = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (a);
}
/**
 * _strcpy - functions that copies a string
 * @dest: the memory location where
 * the resulting data will be stored
 * @src: the memory location of source data
 *
 * Return: pointer to where the resulting
 * data is stored.
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}
