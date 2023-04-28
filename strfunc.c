#include "header.h"

/**
 * _strcomp - compares two strings
 * @s1: char
 * @s2: char
 * Return: integer value
 */
int _strcomp(const char *s1, const char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}

/**
 * _strlen - returns the length of a string
 * @s: character
 * i - integer
 * Return: integer value of lenght
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;
	return (i);
}

/**
 * _strcat - concatenates two strings
 * @dest: final char
 * @src: source char
 * i - integer
 * j - integer
 * Return: concatenated character
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++, i++)
		dest[i] = src[j];
	dest[i] = '\0';
	return (dest);
}

/**
 * _countstring - counts number of words in string
 * @str: pointer to string
 *
 * Return: number of words in string
 */
int _countstring(char *str)
{
	int i;
	int flag = 1;
	int count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && flag == 1)
		{
			count += 1;
			flag = 0;
		}
		if (str[i + 1] == ' ')
			flag = 1;
	}
	return (count);
}

/**
 * _strdup - duplicates a string
 * @str: pointer to string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	int i;
	char *dest_str;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		;
	dest_str = malloc(sizeof(char) * (i + 1));
	if (dest_str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		dest_str[i] = str[i];
	}
	dest_str[i] = '\0';
	return (dest_str);
}

