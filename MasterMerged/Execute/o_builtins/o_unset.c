#include "../execute.h"

static t_envlist *get_before_last(t_envlist *env)
{
    while (env->next->next) // protect from segfault.
        env = env->next;
    return (env);
}

static t_envlist *get_last(t_envlist *env)
{
    while (env->next)
        env = env->next;
    return (env);
}


static  void delete(t_envlist *node)
{
    free(node->value);
    free(node->variable);
    free(node);
}

static void delete_node(t_envlist **env, t_envlist *to_delete)
{
    t_envlist *curr = *env;
    t_envlist *prev = NULL;

    while (curr)
    {
        if (curr == to_delete)
        {
            if (prev)
                prev->next = curr->next;
            else
                *env = curr->next;  // deleting head

            delete(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// scans the envlist and finds argument node to unset it.
static void unset_node(char *argument, t_envlist **env)
{
    t_envlist *curr;

    if (!*env || ft_strcmp(argument, "_") == 0)
        return ; // gotta check if env is 
    curr = *env;
    while (curr)
    {
        if (ft_strcmp(argument, curr->variable) == 0)
        {
            delete_node(env, curr);
            break;
        }
        curr = curr->next;
    }

}

// function entry.
int o_unset(t_tree *node, t_data *data)
{
    size_t      argc;
    int         i;

    argc = arg_count(node->argv);
    if (argc == 1)
        return (EXIT_SUCCESS);
    i = 1;
    while (node->argv[i])
    {
        unset_node(node->argv[i], &data->env);
        i++;
    }
    return (EXIT_SUCCESS);
}


// itereate through the lest 
    // use strncmp on the argv arguments to find the variable to unset and delete it from the list
    // if the varibale doenst exit do nothing
    // if the unset is called with 0 args do nothing



   // some functions set env to null protect dont forget all functions that access env