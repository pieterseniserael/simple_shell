#include "shell.h"

/**
 * _myenv - Displays the current environment variables.
 * @info: A structure containing potential arguments. This structure helps
 *        maintain a constant function prototype.
 *
 * This function is responsible for showing the current environment variables.
 *
 * Return: Always returns 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: A structure containing potential arguments. This structure helps
 *        maintain a consistent function prototype.
 * @name: The name of the environment variable.
 *
 * This function is used to fetch the value associated with a
 * given environment variable.
 *
 * Return: The value of the specified environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable or
 * update an existing one.
 * @info: A structure containing potential arguments. This structure ensures
 *        a consistent function prototype.
 *
 * This function is responsible for initializing a new environment variable
 * or modifying an existing one. It always returns 0.
 *
 * Return: Always returns 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Delete an environment variable.
 * @info: A structure containing potential arguments. This structure helps
 *        maintain a constant function prototype.
 *
 * This function is utilized to remove an existing environment variable.
 * It always returns 0.
 *
 * Return: Always returns 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Fills a linked list with environment variable data.
 * @info: A structure containing potential arguments. This structure ensures
 *        a consistent function prototype.
 *
 * This function is responsible for populating a linked list with data from
 * environment variables. It always returns 0.
 *
 * Return: Always returns 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
