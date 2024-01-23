#include "shell.h"
/**
 * pi_inputbuffers - buffers the chained commands
 * @inf: first parameter
 * @buffer: contains address of the buffer
 * @length: cotains address of length variable
 * Return: bytes read
 */

ssize_t pi_inputbuffers(info_t *inf, char **buffer, size_t *length);
ssize_t pi_inputbuffers(info_t *inf, char **buffer, size_t *length)
{
	ssize_t real = 0;
	size_t len_pointer = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, my_sigintHandler);

#if MYUSE_GETLINER
		real = getline(buffer, &len_pointer, stdin);
#else
		real = my_getline(inf, buffer, &len_pointer);
#endif

		if (real > 0)
		{
			if ((*buffer)[real - 1] == '\n')
			{
				(*buffer)[real - 1] = '\0';
				real--;
			}
			inf->mylineflag = 1;
			my_removecomments(*buffer);
			my_buildhistorylist(inf, *buffer, inf->hcount++);

			if (my_strchr(*buffer, ';'))
			{
				*length = real;
				inf->mycmduf = buffer;
			}
		}

	return (real);
	}
	return (0);
}
/**
 * pi_getinput - gets input from stream
 * @inf: parameter struct
 * Return: always an unsigned int
 */
ssize_t pi_getinput(info_t *inf)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t real = 0;
	char **buf = &(inf->argsm), *point;

	_putchar(MYBUFLUSH);
	real = _inputbuffers(inf, &buffer, &length);
	if (real == -1)
		return (-1);
	if (length)
	{
		b = a;
		point = buffer + a;

		my_checkchain(inf, buffer, &b, a, length);

		for (; b < length; b++)
		{
			if (my_ischain(inf, buffer, &b))
			{
				break;
			}
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			inf->cmdtype = MYCMDSNORMER;
		}

		*buf = point;
		return (my_strlen(point));
	}

	*buf = buffer;
	return (real);
}
/**
 * pi_readbuf - reads a items of a buffer
 * @inf: parameter struct
 * @buffer: buffer
 * @in: size
 * Return: always an unsigned int
 */
ssize_t pi_readbuf(info_t *inf, char *buffer, size_t *in)
{
	ssize_t real = 0;

	if (*in)
		return (0);
	real = read(inf->reader, buffer, MYREADSIZE);
	if (real >= 0)
	{
		*in = real;
	}
	return (real);
}
/**
 * pi_getline - gets the next line of input from an input stream
 * @inf: parameter struct
 * @pointer: address of pointer to buffer
 * @len: size of allocated pointer buffer
 * Return: always an integer
 */
int pi_getline(info_t *inf, char **pointer, size_t *len)
{
	static char buffer[MYREADSIZE];
	static size_t a, length;
	size_t b;
	ssize_t real = 0, c = 0;
	char *point = NULL, *mynew_point = NULL, *d;

	point = *pointer;
	if (point && len)
		c = *len;
	if (a == length)
		a = length = 0;

	real = my_readbuf(inf, buffer, &length);
	if (real == -1 || (real == 0 && length == 0))
	{
		return (-1);
	}

	d = pi_strchr(buffer + a, '\n');
	b = d ? 1 + (unsigned int)(d - buffer) : length;
	mynew_point = my_realloc(point, c, c ? c + b : b + 1);

	if (!mynew_point)
		return (!point ? free(point), -1 : -1);

	if (c)
	{
		pi_strncat(mynew_point, buffer + a, b - a);
	}
	else
	{
		pi_strncpy(mynew_point, buffer + a, b - a + 1);
	}

	c += b - a;
	a = b;
	point = mynew_point;

	if (len)
	{
		*len = c;
	}
	*pointer = point;
	return (c);
}
/**
 * pi_sigintHandler - blocks ctrl-C functions
 * @mysigum: the signal number
 */
void pi_sigintHandler(__attribute__((unused)) int mysigum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(MYBUFLUSH);
}
