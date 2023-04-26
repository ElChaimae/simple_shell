# include "main.h"

/**
 * _getenv - function that gets an environment variable
 * @name: name of the environment variable
 *
 * Return: value of the environment variable, NULL if not found
 */
char *_getenv(const char *name)
{
	size_t len = strlen(name);
	char **p = environ;

	for (; *p; ++p)
	{
		if (strncmp(*p, name, len) == 0 && (*p)[len] == '=')
			return (*p + len + 1);
	}
	return (NULL);
}
