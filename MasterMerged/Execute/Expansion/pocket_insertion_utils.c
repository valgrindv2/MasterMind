#include "../execute.h"

void fail_procedure(char **pockets, t_data *data)
{
	while (--data->pc.j >= 0)
		free(pockets[data->pc.j]);
	free(pockets);
}

bool ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

// expands exit status && pid.
char *expand_special_cases(char *str, t_data *data, int *i)
{
    if (str[*i + 1] == '?')
    {
	    *i += 2; // move $ ? ==> +2 
        return (o_ft_itoa(data->exit_status));
    }
    else if (str[*i + 1] == '$')
    {
        *i += 2; // move $ $ ==> +2 
        return (o_ft_itoa(data->pid));
    }
    return (NULL); // fallback should never happen.
}