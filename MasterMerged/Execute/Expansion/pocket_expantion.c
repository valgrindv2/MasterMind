#include "../execute.h"

// these functions are called from pocket_insertion.

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char    *normal_text(char *str, int *i)
{
    int start;

    start = *i;
	while (str[*i] && str[*i] != '$')
			(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *standalone(int *i)
{
    (*i)++;
    return (ft_strdup("$"));
}

char *expand_key_wrapper(char *str, t_data *data)
{
    data->pc.value = expand_key(str, data, data->pc.keylen, &data->pc.i);
    if (data->pc.value != NULL)
        return (data->pc.value);
    else if (data->pc.value == NULL)
        return(NULL);
    return (perror("WHY!"), NULL); // fallback should never happen
}
