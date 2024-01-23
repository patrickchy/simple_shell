#include "shell.h"
/**
 * pi_gethistoryfile - entry
 * @inf: information
 * Return: NULL or BUff
 */
char *pi_gethistoryfile(info_t *inf);
char *pi_gethistoryfile(info_t *inf)
{
	char *direct = pi_getenv(inf, "HOME=");
	char *buff;

	if (!direct)
		return (NULL);

	buff = malloc(pi_strlen(direct) + pi_strlen(MYHISTFILE) + 2);

	if (!buff)
		return (NULL);

	pi_strcpy(buff, direct);
	pi_strcat(buff, "/");
	pi_strcat(buff, MYHISTFILE);

	return (buff);
}
/**
 * pi_writehistory - entry
 * @inf: infomation
 * Return: 1 or 0
 */
int pi_writehistory(info_t *inf)
{
	ssize_t fid;
	char *file_names = pi_gethistoryfile(inf);
	list_t *noder = inf->pi_history;

	if (!file_names)
		return (-1);

	fid = open(file_names, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_names);

	if (fid == -1)
		return (-1);

	while (noder)
	{
		my_putsfd(noder->string, fid);
		my_putfd('\n', fid);
		noder = noder->nexts;
	}

	my_putfd(MYBUFLUSH, fid);
	close(fid);

	return (1);
}
/**
 * read_history - history entry
 * @inf: history information
 * Return: 1 or 0
 */
int read_history(info_t *inf);
int read_history(info_t *inf)
{
	int a, mylast = 0, myline_count = 0;
	ssize_t fid, myrlen, myf_size = 0;
	struct stat stats;
	char *buffer = NULL, *file_names = pi_gethistoryfile(inf);

	if (!file_names)
		return (0);

	fid = open(file_names, O_RDONLY);
	free(file_names);
	if (fid == -1)
		return (0);

	if (!fstat(fid, &stats))
		myf_size = stats.st_size;

	if (myf_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (myf_size + 1));
	if (!buffer)
		return (0);

	myrlen = read(fid, buffer, myf_size);
	buffer[myf_size] = 0;

	if (myrlen <= 0)
	{
		free(buffer);
		return (0);
	}

	close(fid);

	for (a = 0; a < myf_size; a++)
	{
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			pi_buildhistorylist(inf, buffer + mylast, myline_count++);
			mylast = a + 1;
		}
	}

	if (mylast != a)
	{
		pi_buildhistorylist(inf, buffer + mylast, myline_count++);
	}

	free(buffer);
	inf->hcount = myline_count;

	while (inf->hcount-- >= MYHISTMAX)
	{
		my_delete(&(inf->pi_history), 0);
	}

	pi_renumberhistory(inf);
	return (inf->hcount);
}
/**
 * pi_buildhistorylist - entry
 * @inf: info build
 * @buffer: buffer
 * @myline_count: count line
 * Return: 0 or 1
 */
int pi_buildhistorylist(info_t *inf, char *buffer, int myline_count)
{
	list_t *noder = inf->pi_history;

	pi_addnodeend(&noder, buffer, myline_count);

	inf->pi_history = noder;

	return (0);
}
/**
 * pi_renumberhistory - enter
 * @inf: remmenber info
 * Return: hcount
 */
int pi_renumberhistory(info_t *inf)
{
	list_t *noder = inf->pi_history;
	int a = 0;

	while (noder)
	{
		noder->number = a++;
		noder = noder->nexts;
	}

	return (inf->hcount = a);
}
