#include "../execute.h"

static char **fill_files_array(int count)
{
    DIR             *dir;
    struct dirent   *entry;
    char            **files;
    int             i;

    if (count == 0)
        return (NULL);
    files = malloc(sizeof(char *) * (count + 1));
    if (!files)
        return (NULL);
    dir = opendir(".");
    if (!dir)
        return (free(files), NULL);
    i = 0;
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] != '.')
        {
            files[i] = ft_strdup(entry->d_name);
            i++;
        }
    }
    return (files[i] = NULL, closedir(dir), files);
}

char **get_all_files(void)
{
    int count;

    count = count_files();
    return (fill_files_array(count));
}

static t_arg *create_arg_node(char *value, t_grammar tok)
{
	t_arg *new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->tok = tok;
	new->was_s_quote = 0;
	new->was_d_quote = 0;
	new->space_next = 1;
	new->next = NULL;
	return (new);
}

int expand_star_in_arg(t_arg *arg)
{
	char	**files;
	t_arg	*curr;
	t_arg	*next;
	int		i;

	files = get_all_files();
	if (!files || !files[0])
		return (EXIT_SUCCESS);
    sort_files(files);
	next = arg->next;
	free(arg->value);
	arg->value = ft_strdup(files[0]);
	arg->was_s_quote = 0;
	arg->was_d_quote = 0;
	arg->space_next = 1;
	curr = arg;
	i = 1;
	while (files[i])
	{
		t_arg *new_node = create_arg_node(files[i++], curr->tok);
		if (!new_node)
			return (free_argv(files), EXIT_FAILURE);
		curr->next = new_node;
		curr = new_node;
	}
	return (curr->next = next, free_argv(files), EXIT_SUCCESS);
}

int	try_expand_wildcard(t_arg *arg)
{
	if (arg->was_s_quote)
		return (EXIT_SUCCESS);
	if (arg->was_d_quote)
		return (EXIT_SUCCESS);
	if (!ft_strchr(arg->value, '*') || ft_strcmp(arg->value, "*"))
		return (EXIT_SUCCESS);
	if (expand_star_in_arg(arg) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
