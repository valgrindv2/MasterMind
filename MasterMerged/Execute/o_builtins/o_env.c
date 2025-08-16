#include "../execute.h"

// function entry.
int o_env(t_tree *node, t_data *data)
{
    t_envlist *curr;

    if (node->argv[1])
    {
        puterror("Master@Mind: env: does not support args\n");
        return (EXIT_FAILURE);
    }
    curr = data->env;
    while(curr != NULL)
    {
        if (curr->exported && curr->value)
        {
            printf(YLW"%s", curr->variable);
            printf(RED"=%s"RST"\n", curr->value);
        }
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}