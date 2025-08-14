#include "../execute.h"

static void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;
	size_t			mult;

	mult = count * size;
	if (count && mult / count != size)
		return (NULL);
	ptr = malloc(sizeof(char) * mult);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < mult)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

static int	count_dollars(char *s)
{
	int	i;
	int	count;

    i = 0;
    count = 0;
	while (s[i])
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	return (count);
}

// function entry for expanding a variable can be "$HOME" or "this $USER, is $HOME"
char	*expand_var(char *str, t_data *data, bool was_d_quoted)
{
	char	*expanded;
	int		dollar_count;


    if (str[0] == '\0')
        return (ft_strdup("")); // empty case.
	dollar_count = count_dollars(str);
	data->pockets = ft_calloc((dollar_count * 2 + 2), sizeof(char *)); // $x  1 * 2 ==> 2 +2 4 [""][x value][""][NULL]
	if (!data->pockets)
		return (NULL);
	data->pc.cap = (size_t)(dollar_count * 2 + 2);
	if (pocket_insertion(data->pockets, str, data, was_d_quoted) != EXIT_SUCCESS)
		return (NULL);

	expanded = pocket_joiner(data->pockets);
	if (!expanded)
		return (free_argv(data->pockets), NULL);
	free_argv(data->pockets);
	return (expanded);
}

// core expanding function. expands the argument linked list.
int expand_list(t_arg *arg, t_data *data)
{
    t_arg   *curr;
    char    *expanded;
	char	*first_arg;

    curr = arg;
	first_arg = ft_strdup(curr->value);
    while (curr)
    {
        if (!curr->was_s_quote) // if not single quoted, expand
        {
            expanded = expand_var(curr->value, data, curr->was_d_quote); // wouldnt need pocket expansion algo we will do it differently
            if (!expanded)
                return (EXIT_FAILURE);
            free(curr->value);
            curr->value = expanded;
        }
		if (try_expand_wildcard(curr) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
        // skips over literal strings s quoted, aymane trims those quotes anyway.
        curr = curr->next;
    }
	free(first_arg);
    return (EXIT_SUCCESS);
}
