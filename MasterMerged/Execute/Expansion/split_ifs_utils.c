#include "../execute.h"

bool	has_delim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)1)
			return (true);
		i++;
	}
	return (false);
}

bool	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}
