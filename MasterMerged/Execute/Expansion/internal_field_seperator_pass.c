#include "../execute.h"

// static char *eliminate_ifs_equal(char *str)
// {
//     char    **split;
//     int     i;
//     char    *joined;
//     char    *full;
//     char    *key;

//     split = ft_split(str, (char)1);
//     if (!split)
//         return (NULL);
//     i = 1;
//     key = ft_strdup(split[0]);
//     if (!key)
//         return (free_argv(split), NULL);
//     joined = strjoiner(split + 1, " ", arg_count(split + 1));
//     if (!joined)
//         return (free(key), free_argv(split), NULL);
//     full = ft_strjoin(key, joined);
//     if (!full)
//          return (free(joined), free(key), free_argv(split), NULL);
//     return (free(joined), free(key), free_argv(split), full);
// }

// static int join_ifs_segments(t_ifs_vars *ifs, char **joined)
// {
// 	char	*tmp;

// 	while (ifs->ifs_split[ifs->j + 1]
// 		&& should_join(*joined, ifs->ifs_split[ifs->j + 1]))
// 	{
// 		tmp = gnl_ft_strjoin(*joined, ifs->ifs_split[ifs->j + 1]);
// 		free(*joined);
// 		*joined = tmp;
// 		if (!*joined)
// 			return (EXIT_FAILURE);
// 		ifs->j++;
// 	}
// 	return (EXIT_SUCCESS);
// }

// static int append_ifs(t_ifs_vars *ifs, char *str)
// {
// 	char	*joined;

// 	ifs->ifs_split = ft_split(str, (char)1);
// 	if (!ifs->ifs_split)
// 		return (EXIT_FAILURE);

// 	ifs->j = 0;
// 	while (ifs->ifs_split[ifs->j])
// 	{
// 		joined = ft_strdup(ifs->ifs_split[ifs->j]);
// 		if (!joined)
// 			return (free_argv(ifs->ifs_split), EXIT_FAILURE);

// 		if (join_ifs_segments(ifs, &joined) != EXIT_SUCCESS)
// 			return (free(joined), free_argv(ifs->ifs_split), EXIT_FAILURE);

// 		if (add_ifs_back(&ifs->ifs_list, joined) != EXIT_SUCCESS)
// 			return (free(joined), free_argv(ifs->ifs_split), EXIT_FAILURE);

// 		free(joined);
// 		ifs->j++;
// 	}

// 	free_argv(ifs->ifs_split);
// 	return (EXIT_SUCCESS);
// }

static int append_ifs(t_ifs_vars *ifs, char *str)
{
    ifs->ifs_split = ft_split(str, (char)1);
    if (!ifs->ifs_split)
        return (EXIT_FAILURE);
    ifs->j = 0;
    while (ifs->ifs_split[ifs->j])
    {
        if (add_ifs_back(&ifs->ifs_list, ifs->ifs_split[ifs->j++]) != EXIT_SUCCESS)
            return ( free_argv(ifs->ifs_split), EXIT_FAILURE);
    }
    free_argv(ifs->ifs_split);
    return (EXIT_SUCCESS);
}

// // takes the argv but is joined i want to resplit but only the parts that have the delims i put
char    **ifs_pass(char **argv)
{
    t_ifs_vars  ifs;

    ifs.i = 0;
    ifs.ifs_list = NULL;
    while (argv[ifs.i])
    {
        if (has_delim(argv[ifs.i]))
        {
            if (append_ifs(&ifs, argv[ifs.i]) != EXIT_SUCCESS)
                return (free_ifs_list(ifs.ifs_list), NULL);
        }
        else
        {
            if (add_ifs_back(&ifs.ifs_list, argv[ifs.i]) != EXIT_SUCCESS)
                return (free_ifs_list(ifs.ifs_list), NULL);
        }
       ifs.i++;
    }
    ifs.new_argv = ifs_list_to_argv(ifs.ifs_list);
    if (!ifs.new_argv)
        return (free_ifs_list(ifs.ifs_list), NULL);
    return (free_ifs_list(ifs.ifs_list), ifs.new_argv);
}

char *red_ifs_pass(char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	cleaned = malloc(sizeof(char) * (o_ft_strlen(str) + 1));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != (char)1 && str[i] != (char)127)
		{
			cleaned[j] = str[i];
			j++;
		}
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

