#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t infoz[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				pi_eputs(av[0]);
				pi_eputs(": 0: Can't open ");
				pi_eputs(av[1]);
				pi_eputchar('\n');
				pi_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoz->readfd = fd;
	}
	_populate_env_list(infoz);
	read_history(infoz);
	hsh(infoz, av);
	return (EXIT_SUCCESS);
}
