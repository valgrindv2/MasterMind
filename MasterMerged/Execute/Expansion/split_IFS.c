#include "../execute.h"

bool    has_delim(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (char)27)
            return (true);
        i++;
    }
    return (false);
}

bool    has_space(char *str)
{
    int i;

    i = 0;
    if (!str)
    {
        printf("null str\n");
        exit(1);
    }
    while (str[i])
    {
        if (str[i] == ' ')
            return (true);
        i++;
    }
    return (false);
}

static  char *append_delimiter(char *str)
{
    char    *first_border;
    char    *last_border;
    char    delim[2];

    delim[0] = (char)27;
    delim[1] = '\0';

    first_border= ft_strjoin(delim, str);
    if (!first_border)
        return (NULL);
    last_border = ft_strjoin(first_border, delim);
    if (!last_border)
        return (free(first_border), NULL);
    free(first_border);
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

int internal_field_seperator(char *raw, t_data *data, char ***pockets)
{
    char    **mini_pocket;
    char    **new_pocket;
    size_t  mc_argc;
    size_t  i;

    mini_pocket = ft_split(raw, ' '); // might have to add tabs and \n
    if (!mini_pocket)
        return (EXIT_FAILURE);
    mc_argc = arg_count(mini_pocket);
    if (data->pc.j + mc_argc > data->pc.cap)
    {
        new_pocket = realloc_pockets(*pockets, data->pc.j, data->pc.j + mc_argc);
        if (!new_pocket)
            return (free_argv(mini_pocket), EXIT_FAILURE);
        *pockets = new_pocket;
        data->pc.cap = data->pc.j + mc_argc;
    }
    i = 0;
    while (i < mc_argc)
    {
        (*pockets)[data->pc.j] = append_delimiter(mini_pocket[i++]);
        if (!(*pockets)[data->pc.j++])
            return (free_argv(mini_pocket), EXIT_FAILURE);
    }
    return (free_argv(mini_pocket), EXIT_SUCCESS);
}
