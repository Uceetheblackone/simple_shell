#include "sshell.h"
/**
 * find_path - finds this cmd in the PATH string
 * @mydata: the mydata struct
 * @paths: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(char *mydata, char *paths, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(mydata, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = dup_chars(paths, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(mydata, path))
				return (path);
			if (!paths[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmd - determines if a file is an executable command
 * @mydata: the mydata struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *mydata, char *paths)
{
	struct stat st;

	(void)mydata;
	if (!paths || stat(paths, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @paths: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *paths, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (paths[i] != ':')
			buf[k++] = paths[i];
	buf[k] = 0;
	return (buf);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
