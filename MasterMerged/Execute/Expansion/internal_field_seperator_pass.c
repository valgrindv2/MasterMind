#include "../execute.h"

static size_t ifs_list_size(t_ifs *curr)
{
    size_t size;

    size = 0;
    while (curr)
    {
        size++;
        curr = curr->next;
    }
    return (size);
}

// gets used in terminate anons.
int  add_ifs_back(t_ifs **head, char *str)
{
    t_ifs   *new;
    t_ifs   *curr;

    new = malloc (sizeof(t_ifs));
    if (!new)
        return (EXIT_FAILURE);
    new->string = ft_strdup(str);
    if (!new->string)
        return (free(new), EXIT_FAILURE);
    new->next = NULL;
    if (!*head)
        *head = new;
    else
    {
        curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
    return (EXIT_SUCCESS);
}

char **ifs_list_to_argv(t_ifs *head)
{
    size_t  size;
    t_ifs   *curr;
    char    **argv;
    size_t  i;

    i = 0;
    size = ifs_list_size(head);
    argv = malloc(sizeof(char *) * (size + 1));
    if (!argv)
        return (NULL);
    curr = head;
    while (i < size)
    {
        argv[i] = ft_strdup(curr->string);
        if (!argv[i])
        {
            while (--i >= 0)
                free(argv[i]);
            return (free(argv), NULL);
        }
        curr = curr->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

static char *eliminate_ifs_equal(char *str)
{
    char    **split;
    int     i;
    char    *joined;
    char    *full;
    char    *key;

    split = ft_split(str, (char)1);
    if (!split)
        return (NULL);
    i = 1;
    key = ft_strdup(split[0]);
    if (!key)
        return (free_argv(split), NULL);
    joined = strjoiner(split + 1, " ", arg_count(split + 1));
    if (!joined)
        return (free(key), free_argv(split), NULL);
    full = ft_strjoin(key, joined);
    if (!full)
         return (free(joined), free(key), free_argv(split), NULL);
    return (free(joined), free(key), free_argv(split), full);
}

static int append_ifs(t_ifs_vars *ifs, char *str)
{
    if (has_equal(str))
    {
        ifs->string = eliminate_ifs_equal(str);
        if (!ifs->string)
            return (EXIT_FAILURE);
        if (add_ifs_back(&ifs->ifs_list, ifs->string) != EXIT_SUCCESS)
            return (free(ifs->string), ifs->string = NULL, EXIT_FAILURE);
        free(ifs->string);
        ifs->string = NULL;
        return(EXIT_SUCCESS);
    }
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

char    *red_ifs_pass(char *str)
{
    char    **ifs_split;
    char    *joined;

    if (str[0] == '\0')
        return (ft_strdup(""));
    ifs_split = ft_split(str, (char)1);
    if (!ifs_split)
        return (NULL);
    joined = strjoiner(ifs_split, " ", arg_count(ifs_split));
    if (!joined)
        return (free_argv(ifs_split), NULL);
    return (joined);
}
