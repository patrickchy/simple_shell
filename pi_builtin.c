#include "shell.h"

/**
 *pi_myexit - Exits the shell
 * @infoz: Pointer to the  structure containing potential arguments
 * that is used to maintain
 *          constant function prototype.
 *  Return: Exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int pi_myexit(info_t *infoz)
{
	int exitcheck;

	if (infoz->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(infoz->argv[1]);
		if (exitcheck == -1)
		{
			infoz->status = 2;
			print_error(infoz, "Illegal number: ");
			_eputs(infoz->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infoz->err_num = _erratoi(infoz->argv[1]);
		return (-2);
	}
	infoz->err_num = -1;
	return (-2);
}

/**
 * pi_mycd - Changes the current directory of the process
 * @infoz: Pointer to the structure containing potential arguments.
 * tht is used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int pi_mycd(info_t *infoz)
{
	char *si, *dirr, buffer[1024];
	int ch_diret;

	si = getcwd(buffer, 1024);
	if (!si)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infoz->argv[1])
	{
		dirr = _getenv(infoz, "HOME=");
		if (!dirr)
			ch_dirret = /* TODO: what should this be? */
				chdir((dirr = _getenv(info, "PWD=")) ? dirr : "/");
		else
			ch_dirret = chdir(dirr);
	}
	else if (_strcmp(infoz->argv[1], "-") == 0)
	{
		if (!_getenv(infoz, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infoz, "OLDPWD=")), _putchar('\n');
		ch_dirret = /* TODO: what should this be? */
			chdir((dirr = _getenv(infoz, "OLDPWD=")) ? dirr : "/");
	}
	else
		ch_dirret = chdir(infoz->argv[1]);
	if (ch_dirret == -1)
	{
		print_error(infoz, "can't cd to ");
		_eputs(infoz->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infoz, "OLDPWD", _getenv(infoz, "PWD="));
		_setenv(infoz, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * pi_myhelp - Changes the current directory of the process
 * @infoz: Poiter to the structure containing potential arguments.
 * that is used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int pi_myhelp(info_t *infoz)
{
	char **pi_argarray;

	pi_argarray = infoz->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*pi_argarray); /* temp att_unused workaround */
	return (0);
}
