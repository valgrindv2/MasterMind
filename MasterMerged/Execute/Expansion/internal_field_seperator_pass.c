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

static int append_ifs(t_ifs_vars *ifs, char *str)
{
    ifs->ifs_split = ft_split(str, (char)27);
    if (!ifs->ifs_split)
        return (EXIT_FAILURE);
    ifs->j = 0;
    while (ifs->ifs_split[ifs->j])
    {
        if (add_ifs_back(&ifs->ifs_list, ifs->ifs_split[ifs->j++]) != EXIT_SUCCESS)
            return (free_ifs_list(ifs->ifs_list), free_argv(ifs->ifs_split), EXIT_FAILURE);
    }
    free_argv(ifs->ifs_split);
    return (EXIT_SUCCESS);
}

// // takes the argv but is joined i want to resplit but only the parts that have the delims i put
char    **IFS_pass(char **argv)
{
    t_ifs_vars  ifs;

    ifs.i = 0;
    ifs.ifs_list = NULL;
    while (argv[ifs.i])
    {
        if (has_delim(argv[ifs.i]))
        {
            if (append_ifs(&ifs, argv[ifs.i]) != EXIT_SUCCESS)
                return (NULL);
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
