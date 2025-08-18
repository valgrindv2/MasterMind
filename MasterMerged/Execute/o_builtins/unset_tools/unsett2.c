#include "../../execute.h"

int	valide_unset(char *str, int i)
{
	if (str[i] == '+' && str[i + 1] != '=')
		return (false);
	if (str[i] == '=' && !is_printable(str[i + 1]))
		return (false);
	return (true);
}

int	init_mini(int *i, bool *stand)
{
	*i = 0;
	*stand = true;
}
