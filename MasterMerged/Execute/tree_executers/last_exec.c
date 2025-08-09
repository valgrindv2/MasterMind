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
            free(curr->value); // free old value
            curr->value = ft_strdup(last_cmd);
            if (!curr->value)
                return(EXIT_FAILURE);
        }
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}

int add_last_executed(t_tree *node, t_data *data)
{
    if (data->last_executed) // first time will be null so no need to free
        free(data->last_executed);
    data->last_executed = get_last_argv(node->argv);
    if (!data->last_executed)
        return (perror("Last Executed Malloc"), EXIT_FAILURE);
    _env(data->env, data->last_executed);
    free(data->last_executed);
    data->last_executed = NULL;
    return (EXIT_SUCCESS);
}
