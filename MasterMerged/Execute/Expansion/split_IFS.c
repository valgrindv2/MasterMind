#include "../execute.h"

char *append_delimiter(char *str)
{
    char    *first_border;
    char    *last_border;
    char    delim[2];

    delim[0] = (char)1;
    delim[1] = '\0';

    first_border= ft_strjoin(delim, str);
    if (!first_border)
        return (NULL);
    last_border = ft_strjoin(first_border, delim);
    if (!last_border)
        return (free(first_border), NULL);
    free(first_border); // free str
    return (last_border);
}

void free_ifs_list(t_ifs *ifs)
{
    t_ifs   *tmp;

    if (!ifs)
        return ;
    while (ifs)
    {
        tmp = ifs->next;
        free(ifs->string);
        free(ifs);
        ifs = tmp;
    }
}

bool only_spaces(char *raw)
{
    int i;

    i = 0;
    while (raw[i])
    {
        if (raw[i] != ' ')
            return (false);
        i++;
    }
    return (true);
}

int expand_unqoted_d(char ***pockets, t_data *data, char *raw)
{
    int     i;
    int     j;
    char    **new_pocket;
    int     mc_argc;
    char    **split;

    split = tab_split(raw, " \t\n\v\f\r");
    mc_argc = arg_count(split);
    new_pocket = malloc((data->pc.j + mc_argc + 1) * sizeof(char *));
    i = 0;
    while (i < data->pc.j)
    {
        new_pocket[i] = ft_strdup((*pockets)[i]);
        i++;
    }
    j = 0;
    while (split[j])
    {
        new_pocket[i++] = append_delimiter(split[j++]);
    }
    new_pocket[i] = NULL;
    (*pockets) = new_pocket;
    data->pc.j = i;
    return (EXIT_SUCCESS);
}
