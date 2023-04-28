#include "header.h"

/**
 * _splitstring - counts number of words in string
 * @str: pointer to string to count
 *
 * Return: number of words in string
 */
int _splitstring(char *str)
{
	int i;
	int searchflag = 1;
	int wordcount = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && searchflag == 1)
		{
			wordcount += 1;
			searchflag = 0;
		}
		if (str[i + 1] == ' ')
			searchflag = 1;
	}
	return (wordcount);
}

