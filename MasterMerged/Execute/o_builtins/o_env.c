#include "../execute.h"

// function entry.
int o_env(t_tree *node, t_data *data)
{
    t_envlist *curr;

    curr = data->env;
    while(curr != NULL)
    {
        if (curr->exported && curr->value)
            printf("%s=%s\n", curr->variable, curr->value);
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}