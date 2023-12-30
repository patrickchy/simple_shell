#include "shell.h"

/**
 * pi_interactive - Returns true if shell is interactive mode
 * @infoz: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int pi_interactive(info_t *infoz)
{
	return (isatty(STDIN_FILENO) && infoz->readfd <= 2);
}

/**
 * pi_delim - Checks if character is a delimeter
 * @ch: The character to check
 * @delimeter: Pointer to the delimeter string
 * Return: 1 if true, 0 if false
 */
int pi_delim(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}

/**
 *pi_alphabet - Checks for alphabetic character
 *@input: The character to input
 *Return: 1 if inpu is alphabetic, 0 otherwise
 */

int pi_alphabet(int input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *pi_atoi - Converts a string to an integer
 *@st: Pointer to the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int pi_atoi(char *st)
{
	int i, sn = 1, fl = 0, opt = 0;
	unsigned int score = 0;

	for (i = 0;  st[i] != '\0' && fl != 2; i++)
	{
		if (st[i] == '-')
			sn *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			fl = 1;
			score *= 10;
			score += (st[i] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (sn == -1)
		opt = -score;
	else
		opt = score;

	return (opt);
}
