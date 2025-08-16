#include "../execute.h"

size_t ifs_list_size(t_ifs *curr)
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

int is_alphanum_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int should_join(char *curr, char *next)
{
    char last;
    char first;

	if (!curr || !next)
		return (0);
	last = curr[o_ft_strlen(curr) - 1];
	first = next[0];
	if (is_alphanum_underscore(last) && !is_alphanum_underscore(first))
		return (1);
	if (!is_alphanum_underscore(last) && is_alphanum_underscore(first))
		return (1);
	if (!is_alphanum_underscore(last) && !is_alphanum_underscore(first))
		return (1);
	return (0);
}