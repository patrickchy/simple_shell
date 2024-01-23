#include "shell.h"
/**
 * _interactiveness - returns true if shell is interractive
 * @infos: address for struct
 * Return: always 1 for interactive and 0 for non interractive
*/
int _interactiveness(info_t *infos);
int _interactiveness(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->reader <= 2);
}
/**
 * _isdelimeter - checks if a single character is a delimeter
 * @character: the character to check
 * @delimeter: the delimeter string to be used
 * Return: 1 or 0 if true and false respectively
 */
int _isdelimeter(char character, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == character)
			return (1);
	return (0);
}
/**
 * _alphabet - checks for alphabetic character in an input
 * @input: the input to check from
 * Return: 1 for alphabetic, 0 otherwise
 */
int _alphabet(int input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts string to integer
 * @strings: the string to convert
 * Return: an integer
 */
int _atoi(char *strings)
{
	int i = 0, sgn = 1, fg = 0, out = 0;
	unsigned int score = 0;

	for (i = 0; strings[i] != '\0' && fg != 2; i++)
	{
		if (strings[i] == '-')
			sgn *= -1;
		if (strings[i] >= '0' && strings[i] <= '9')
		{
			fg = 1;
			score *= 10;
			score += (strings[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}
	if (sgn == -1)
		out = -score;
	else
		out = score;
	return (out);
}
