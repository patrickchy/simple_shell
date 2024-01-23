#include "shell.h"
/**
 *_eputs - prints an input string to stdout
 * @strings: the string to be printed
 */
void _eputs(char *strings)
{
	int a = 0;

	if (!strings)
		return;

	while (strings[a] != '\0')
	{
		_eputchar(strings[a]);
		a++;
	}
}
/**
 * _eputchar - writes the character to stderr
 * @cha: The character to print
 * Return: always an integer.
 */
int _eputchar(char cha)
{
	static int a;
	static char buffer[_WRITEBUFSIZE];

	if (cha == MYBUFLUSH || a >= _WRITEBUFSIZE)
	{
		write(2, buffer, a);
		a = 0;
	}
	if (cha != MYBUFLUSH)
		buffer[a++] = cha;
	return (1);
}
/**
 * _putfd - writes the character to fid
 * @cha: The character to be writte
 * @fid: filedescriptor to write to
 * Return: always an integer
 */
int _putfd(char cha, int fid)
{
	static int a;
	static char buffer[_WRITEBUFSIZE];

	if (cha == MYBUFLUSH || a >= _WRITEBUFSIZE)
	{
		write(fid, buffer, a);
		a = 0;
	}
	if (cha != MYBUFLUSH)
		buffer[a++] = cha;
	return (1);
}
/**
 * _putsfd - prints an input string to stdout
 * @strings: the string to be printed
 * @fid: the filedescriptor to write to
 * Return: always an integer
 */
int _putsfd(char *strings, int fid)
{
	int a = 0;

	if (!strings)
		return (0);

	for (a = 0; strings[a] != '\0'; a++)
	{
		_putfd(strings[a], fid);
	}

	return (a);
}
