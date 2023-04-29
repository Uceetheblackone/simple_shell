#include "shell.h"

/**
 * get_array_element - gets an element of an array
 * @array: array to be searched
 * @element_name: name of element to be found
 *
 * Return: the array element, or NULL if it is not found
 */
char *get_array_element(char **array, char *element_name)
{
	while (*array != NULL)
	{
		if (str_comp(*array, element_name, PREFIX) == TRUE)
			return (*array);

		array++;
	}

	return (NULL);
}

/**
 * create_array - create a list from a buffer
 * @str: the buffer
 * @delim: character to mark the end of the list entry
 * @is_sep: if the string has semicolons, is_sep becomes the location after the
 * semicolon
 *
 * Return: a pointer to the list
 */
char **create_array(char *str, char delim, char **is_sep)
{
	char *str_ptr = str;
	unsigned int i = 2;
	char **array = NULL;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == ';')
			break;
		if (*str_ptr == delim && *(str_ptr + 1) != '\0')
			i++;

		str_ptr++;
	}

	array = malloc(i * sizeof(char **));
	if (array == NULL)
		exit(EXIT_FAILURE);

	array[0] = str;
	str_ptr = str;
	i = 1;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == delim)
		{
			*str_ptr = '\0';
			str_ptr++;
			if (*str_ptr == ';')
			{
				array[i] = NULL;
				if (*(str_ptr + 1) != '\0' && *(str_ptr + 2) != '\0')
					*is_sep = str_ptr + 2;
				break;
			}
			if (*str_ptr != '\0')
			{
				array[i] = str_ptr;
				i++;
			}
		}
		str_ptr++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * _listlen - finds the length of a list, or the index of an entry
 * @list: list to be evaluated
 * @entry: entry to be indexed
 *
 * Return: length or index if success, -1 if failure
 */
int _listlen(char **list, char *entry)
{
	int i = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			i++;
			list++;
		}
		i++;
		return (i);
	}
	else
	{
		while (*list != NULL)
		{
			if (str_comp(*list, entry, PREFIX) == TRUE)
				return (i);

			i++;
			list++;
		}
	}

	return (-1);
}

/**
 * copy_array - copies an array
 * @old_array: array to be copied
 * @new_size: size of new array
 *
 * Return: the new array
 */
char **copy_array(char **old_array, int new_size)
{
	char **new_array = NULL;
	char **array_ptr;

	new_array = malloc(sizeof(char **) * new_size);

	array_ptr = new_array;
	while (*old_array != NULL)
	{
		*array_ptr = _strdup(*old_array);
		array_ptr++;
		old_array++;
	}
	*array_ptr = NULL;

	return (new_array);
}

/**
 * free_array - frees a two dimensional array
 * @args: array to be freed
 *
 * Return: TRUE
 */
int free_array(char **args)
{
	char **ptr = args;

	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}

	free(args);

	return (TRUE);
}
