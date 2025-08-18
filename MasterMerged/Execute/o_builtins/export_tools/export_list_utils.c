#include "../../execute.h"

bool    has_equal(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (true);
        i++;
    }
    return (false);
}

bool has_plus(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '+' && str [i + 1] == '=')
            return (true);
        i++;
    }
    return (false);
}

void free_exp_list(t_envlist *exp_list)
{
    t_envlist   *tmp;

    if (!exp_list)
        return ;
    while (exp_list)
    {
        tmp = exp_list->next;
        free(exp_list);
        exp_list = tmp;
    }
}

int add_to_export_list(t_envlist **export_lst, t_envlist *env)
{
    t_envlist   *exp_node;
    t_envlist   *curr;

    exp_node = malloc(sizeof(t_envlist));
    if (!exp_node)
        return (EXIT_FAILURE);
    exp_node->variable = env->variable;
    exp_node->value = env->value;
    exp_node->exported = env->exported;
    exp_node->pointed = false;
    exp_node->next = NULL;
    if (!*export_lst)
        *export_lst = exp_node;
    else
    {
        curr = *export_lst;
        while (curr->next)
            curr = curr->next;
        curr->next = exp_node;
    }
    return (EXIT_SUCCESS);
}
