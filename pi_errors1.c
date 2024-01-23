#include "shell.h"
/**
 * _erratoi - will convert a string to an integer
 * @siz: the string to be converted
 * Return: 0 if no number in string, and -1 on error
 */
int _erratoi(char *siz)
{
	int a = 0;
	unsigned long int check = 0;

	if (*siz == '+')
		siz++;

	for (a = 0; siz[a] != '\0'; a++)
	{
		if (siz[a] >= '0' && siz[a] <= '9')
		{
			check *= 10;
			check += (siz[a] - '0');
			if (check > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (check);
}
/**
 * print_error - prints an error message to stdout
 * @inf: first parameter
 * @chestr: string with error type
 * Return: always anteger
 */
void print_error(info_t *inf, char *chestr)
{
	_eputs(inf->my_f_name);
	_eputs(": ");
	_printd(inf->my_linecount, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->my_argv[0]);
	_eputs(": ");
	_eputs(chestr);
}
/**
 * _printd - prints a decimal number
 * @put: the input to be printed
 * @fid: the filedescriptor
 * Return: number of characters printed, always integer
 */
int _printd(int put, int fid)
{
	int (*__putchar)(char) = (fid == STDERR_FILENO) ? _eputchar : _putchar;
	int counter = 0;
	unsigned int rebase = (put < 0) ? -put : put;

	switch (put < 0)
	{
		case 1:
			__putchar('-');
			counter++;
			break;
		default:
			break;
	}

	while (rebase > 0)
	{
		int mydigit = rebase % 10;

		__putchar('0' + mydigit);
		rebase /= 10;
		counter++;
	}

	return (counter);
}
/**
 * convert_number - converters a number
 * @number: number to be converted
 * @bases: the base
 * @flgs: argument flags to be used
 * Return: always a string
 */
char *convert_number(long int number, int bases, int flgs)
{
	static char *marray;
	static char mybuffer[50];
	char mysign = 0;
	char *pointer;
	unsigned long nums = number;

	if (!(flgs & MY_CONVERTUNSIGNED) && number < 0)
	{
		nums = -number;
		mysign = '-';
	}

	marray = flgs & MY_CONVERTLOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &mybuffer[49];
	*pointer = '\0';

	for (; nums != 0; nums /= bases)
	{
		*--pointer = marray[nums % bases];
	}

	if (mysign)
		*--pointer = mysign;
	return (pointer);
}
/**
 * remove_comments - function replaces first occurence of '#' with '\0'
 * @buffer: address of the string to modify
 */
void remove_comments(char *buffer)
{
	int a = 0;

	while (buffer[a] != '\0')
	{
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
		a++;
	}
}
