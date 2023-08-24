#include "shell.h"

/**
 * _myhistory - Displays the history list, presenting 1 command per line,
 *              each accompanied by a line number, starting from 0.
 * @info: A structure containing potential arguments - Maintains a constant
 *        function prototype.
 *
 * This function is responsible for showing the history list of commands,
 * displaying them individually with their corresponding line numbers,
 * Starting from 0. The function always returns 0.
 *
 * Return: Always return 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias and sets it to a string.
 * @info: A struct containing relevant parameters.
 * @str: The string representing the alias.
 *
 * This function is used to unset an alias and then
 * assign it a new string value.
 *
 * Return: Always returns 0 upon success, and 1 upon encountering an error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Assigns an alias to a string.
 * @info: A parameter struct.
 * @str: The string representing the alias.
 *
 * This function is used to establish an alias and associate
 * it with a specified string.
 *
 * Return: Always returns 0 upon success, and 1 upon encountering an error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays the content of an alias string.
 * @node: The alias node to be printed.
 *
 * This function is designed to print out the content of
 * an alias node's string.
 *
 * Return: Always returns 0 upon success, and 1 upon encountering an error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Simulates the behavior of the alias built-in
 * command (refer to 'man alias').
 * @info: A structure containing potential arguments. This structure ensures
 *        a consistent function prototype.
 *
 * This function replicate the functionality of the alias
 * built-in command, allowing for the management of aliases.
 * It always returns 0.
 *
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
