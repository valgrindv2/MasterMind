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

static int append_ifs(t_ifs_vars *ifs, char *str)
{
    ifs->ifs_split = ft_split(str, (char)27);
    if (!ifs->ifs_split)
        return (EXIT_FAILURE);
    print_argv(ifs->ifs_split);
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

char *strjoiner(char **list, char *sep, size_t size)
{
    size_t  total_len;
    size_t  strings_len;
    size_t  i, j, k;
    char    *joined;

    if (!list || !sep || size == 0)
        return (NULL);
    if (size == 1)
        return (ft_strdup(list[0]));
    i = 0;
    strings_len = 0;
    while (list[i])
        strings_len += o_ft_strlen(list[i++]);
    total_len = strings_len + (o_ft_strlen(sep) * (size - 1));
    joined = malloc(total_len + 1);
    if (!joined)
        return (NULL);
    i = 0;
    k = 0;
    while (list[i])
    {
        j = 0;
        while (list[i][j])
            joined[k++] = list[i][j++];
        if (i < size - 1)
        {
            j = 0;
            while (sep[j])
                joined[k++] = sep[j++];
        }
        i++;
    }
    joined[k] = '\0';
    return (joined);
}


char    *red_IFS_pass(char *str)
{
    char    **ifs_split;
    char    *joined;

    if (str[0] == '\0')
        return (ft_strdup(""));
    ifs_split = ft_split(str, (char)27);
    if (!ifs_split)
        return (NULL);
    joined = strjoiner(ifs_split, " ", arg_count(ifs_split));
    puts(joined);
    if (!joined)
        return (free_argv(ifs_split), NULL);
    return (joined);
}
