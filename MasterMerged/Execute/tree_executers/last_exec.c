#include "../execute.h"

static char *get_last_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        i++;
    return (ft_strdup(argv[i - 1]));
    
}


int _env(t_envlist *env, char *last_cmd)
{
    t_envlist *curr;

    curr = env;
    while (curr)
    {
        if (ft_strcmp("_", curr->variable) == 0)
        {
            curr->value = allocate_gc(ft_strdup(last_cmd));
            if (!curr->value)
                return(EXIT_FAILURE);
        }
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}

int add_last_executed(t_tree *node, t_data *data)
{
    data->last_executed = allocate_gc(get_last_argv(node->argv));
    _env(data->env, data->last_executed);
    data->last_executed = NULL;
    return (EXIT_SUCCESS);
}
