#include "../../execute.h"

static bool printable(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (char)127)
            return (false);
        i++;
    }
    return (true);
}

static void print_export_list(t_envlist *env)
{
    t_envlist *curr;

    curr = env;
    while (curr)
    {
        printf("declare -x %s", curr->variable);
        if (printable(curr->value))
            printf("=\"%s\"",curr->value);
        printf("\n");
        curr = curr->next;
    }
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

//entry function.
int o_export(t_tree *node, t_data *data)
{
    int         argc;
    t_envlist   *export_lst;
    int         i;

    argc = arg_count(node->argv);
    export_lst = NULL;
    if (sort_list(&export_lst, data->env) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    if (argc == 1)
        print_export_list(export_lst);
    else
    {
        i = 1;
        while (node->argv[i])
        {
            if (process_export_arg(node->argv[i], data) != EXIT_SUCCESS)
                return (free_exp_list(export_lst), EXIT_FAILURE);
            i++;
        }
    }
    if (data->exit_status == 1 && data->export_status == true)
        return (free_exp_list(export_lst), data->exit_status = 1, EXIT_SUCCESS);
    return (free_exp_list(export_lst), data->exit_status = 0, EXIT_SUCCESS);
}
