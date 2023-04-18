#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* main - Entry Point
*
* Return: Always 0.
*/

int main(void)
{
	/* Define a string to be printed*/
	char output[] = "Hello, BelnJu!\n";

	/* Calculate the length of the string*/
	int len = sizeof(output) - 1;  /* subtract 1 to exclude the null terminator*/

	/* Loop through each character in the string*/
	int i;

	for (i = 0; i < len; i++)
	{

	/**
	*Use the write() function to print the
	* character to the standard output (stdout)
	*/
	write(STDOUT_FILENO, &output[i], 1);
	}

	return (0);
}
