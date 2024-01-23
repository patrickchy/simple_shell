#include "shell.h"

/**
 *my_history - Function to display the history list, one command by line,
 * preceded
 *              with line numbers, starting at 0.
 * @infoz: Pointer to the structure containing potential arguments.
 * that is used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(info_t *infoz)
{
	print_list(infoz->history);
	return (0);
}

/**
 * un_setalias - Sets alias to string
 * @infoz: Ponter to the parameter struct
 * @st: Poiinter to the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int un_setalias(info_t *infoz, char *st)
{
	char *pi_pointer, c;
	int result;

	pi_pointer = _strchr(st, '=');
	if (!pi_pointer)
		return (1);
	c = *pi_pointer;
	*pi_pointer = 0;
	result = delete_node_at_index(&(infoz->alias),
		get_node_index(infoz->alias, node_starts_with(infoz->alias, st, -1)));
	*pi_pointer = c;
	return (result);
}

/**
 * _setalias - Sets alias to string
 * @infoz: Pointer to the parameter struct
 * @st: Pointer to the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _setalias(info_t *infoz, char *st)

	char *pi_pointer;

	pi_pointer = _strchr(str, '=');
	if (!pi_pointer)
		return (1);
	if (!*++pi_pointer)
		return (un_setalias(infoz, st));

	un_setalias(infoz, sr);
	return (add_node_end(&(infoz->alias), st, 0) == NULL);
}

/**
 * print_alias - Function prints an alias string
 * @node: Pointer to the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *pi_pointer = NULL, *a = NULL;

	if (node)
	{
		pi_pointer = _strchr(node->st, '=');
		for (a = node->st; a <= pi_pointer; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pi_pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Copies the alias builtin (man alias)
 * @infoz: Pointer to the structure containing potential arguments.
 * that is used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(info_t *infoz)
{
	int i = 0;
	char *pi_pointer = NULL;
	list_t *node = NULL;

	if (infoz->argc == 1)
	{
		node = infoz->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infoz->argv[i]; i++)
	{
		pi_pointer = _strchr(infoz->argv[i], '=');
		if (pi_pointer)
			_setalias(infoz, infoz->argv[i]);
		else
			print_alias(node_starts_with(infoz->alias, infoz->argv[i], '='));
	}

	return (0);
}
