#include "../execute.h"

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

static void free_exp_list(t_envlist *exp_list)
{
    t_envlist   *tmp;

    if (!exp_list)
        return ;
    while (exp_list)
    {
        tmp = exp_list->next;
        free(exp_list->value);
        free(exp_list->variable);
        free(exp_list);
        exp_list = tmp;
    }
}

static void print_export_list(t_envlist *env)
{
    t_envlist *curr;

    curr = env;
    while (curr)
    {
        printf("declare -x %s=\"%s\"\n", curr->variable, curr->value);
        curr = curr->next;
    }
    // free copy
}

static int add_to_export_list(t_envlist **export_lst, t_envlist *env)
{
    t_envlist   *exp_node;
    t_envlist   *curr;

    exp_node = malloc(sizeof(t_envlist)); //free only this node later.
    if (!exp_node)
        return (EXIT_FAILURE);
    exp_node->variable = env->variable; // same pointers to env data.
    exp_node->value = env->value;
    exp_node->exported = env->value;
    exp_node->pointed = env->value;
    exp_node->next = NULL;
    if (!*export_lst)
    {
        *export_lst = exp_node;
    }
    else
    {
        curr = *export_lst;
        while (curr->next)
            curr = curr->next;
        curr->next = exp_node;
    }
    return (EXIT_SUCCESS);
}

static void sort_operation(t_envlist **exp)
{
        char *tmp_var;
        char *tmp_value;
        t_envlist *trav1;
        t_envlist *trav2;

        trav1 = *exp;
        while(trav1 != NULL)
        {
                trav2 = trav1->next;
                while(trav2 != NULL)
                {
                        if (ft_strcmp(trav1->variable, trav2->variable) > 0)
                        {
                                tmp_var = trav1->variable;
                                tmp_value = trav1->value;
                                trav1->variable = trav2->variable;
                                trav1->value = trav2->value;
                                trav2->variable = tmp_var;
                                trav2->value = tmp_value;
                        }
                        trav2 = trav2->next;
                }
                trav1 = trav1->next;
        }
}

static int sort_list(t_envlist **export_lst, t_envlist *env)
{

    while (env)
    {
        // copy the env list.
        if (add_to_export_list(export_lst, env) != EXIT_SUCCESS)
            return (free_exp_list(*export_lst), EXIT_FAILURE);
        env = env->next;
    }
    sort_operation(export_lst);
    return (EXIT_SUCCESS);
}

// function entry.
int o_export(t_tree *node, t_data *data)
{
    int         argc;
    t_envlist   *export_lst;
    int         i;

    argc = arg_count(node->argv);
    export_lst = NULL;
    // copy and sort list; sorted version.
    if (sort_list(&export_lst, data->env) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    i = 1;
    if (argc == 1) // only export case.
        print_export_list(export_lst);
    else
    {
        while (node->argv[i])
        {
            if (has_equal(node->argv[i]))
                add_to_envlist(&data->env, node->argv[i]); // check if fails.
            i++;
        }
    }
    return (EXIT_SUCCESS);
}

// when export is called
// export with no arguments
//    --> lists export list.
// export with arguments, we loop over the args
//      --> if includes '=' whe add to the env list.
//      --> exoported flag true
//      --> else false