#include "../execute.h"

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
	char	**pockets;
	char	*expanded;
	int		dollar_count;


    if (str[0] == '\0')
        return (ft_strdup("")); // empty case.
	dollar_count = count_dollars(str);
	pockets = malloc(sizeof(char *) * (dollar_count * 2 + 2));
	if (!pockets)
		return (NULL);
	data->pc.cap = (size_t)(dollar_count * 2 + 2);
	if (pocket_insertion(pockets, str, data, was_d_quoted) != EXIT_SUCCESS)
		return (NULL);
	expanded = pocket_joiner(pockets);
	if (!expanded)
		return (free_argv(pockets), NULL);
	free_argv(pockets);
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
			// if (has_star(curr->value))
			// {
			// 	link_patterns_to_argv(curr); // check for fail
			// }
            expanded = expand_var(curr->value, data, curr->was_d_quote);
            if (!expanded)
                return (EXIT_FAILURE);
            free(curr->value);
            curr->value = expanded;
        }
        // skips over literal strings s quoted, aymane trims those quotes anyway.
        curr = curr->next;
    }
	free(first_arg);
    return (EXIT_SUCCESS);
}
