#include "shell.h"
/**
 * p_myenv - entry
 * @inf: info
 * Return: 1 or 0
 */
intp _myenv(info_t *inf)
{
	p_printliststr(inf->p_myenv);
	return (0);
}
/**
 * p_getenv - entry
 * @inf: info
 * @nam: nam
 * Return: pointer
 */
char *p_getenv(info_t *inf, const char *nam)
{
	list_t *noder = inf->p_myenv;
	char *point;

	while (noder)
	{
		point = _startswith(noder->string, nam);
		if (point && *point)
			return (point);
		noder = noder->nexts;
	}
	return (NULL);
}
/**
 * p_mysetenv - entry
 * @inf: info
 * Return: 1 or 0
 */
int p_mysetenv(info_t *inf)
{
	if (inf->p_argc != 3)
	{
		p_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (p_setenv(inf, inf->p_argv[1], inf->p_argv[2]))
		return (0);
	return (1);
}
/**
 * p_myunsetenv - entry
 * @inf: info
 * Return: 1 or 0
 */
int p_myunsetenv(info_t *inf)
{
	int a = 1;

	if (inf->p_argc == 1)
	{
		p_eputs("Too few arguments.\n");
		return (1);
	}

	for (; a <= inf->p_argc; a++)
		p_unsetenv(inf, inf->p_argv[a]);

	return (0);
}
/**
 * p_populateenvlist - entry
 * @inf: info
 * Return: 1 or 0
 */
int p_populateenvlist(info_t *inf)
{
	list_t *noder = NULL;
	size_t a = 0;

	for (; environ[a]; a++)
		p_addnodeend(&noder, environ[a], 0);

	inf->p_env = noder;
	return (0);
}
