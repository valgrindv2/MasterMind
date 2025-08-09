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

static bool has_plus(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '+')
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
        free(exp_list);
        exp_list = tmp;
    }
}

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
        printf(YLW"declare -x %s"RST, curr->variable);
        if (printable(curr->value))
            printf(RED"=\"%s\""RST,curr->value);
        printf("\n");
        curr = curr->next;
    }
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

static  bool    already_exported(char *new_var, t_data *data)
{
    t_envlist   *curr;
    char        *key;

    key = get_key(new_var);
    if (!key)
        return (false);
    curr = data->env;
    while (curr)
    {
        if (ft_strcmp(key, curr->variable) == 0)
            return (free(key), true);
        curr = curr->next;
    }
    return (free(key), false);
}

static int  assign_new_value(char *new_var, t_envlist *env)
{
    char    *key;
    char    *value;

    key = get_key(new_var);
    if (!key)
        return (EXIT_FAILURE);
    value = get_value(new_var);
    if (!value)
        return (free(key), EXIT_FAILURE);
    while (env)
    {
        if (ft_strcmp(key, env->variable) == 0)
        {
            free(env->value);
            env->value = value;
            env->exported = EXPORTED;
            return (free(key), EXIT_SUCCESS);
        }
        env = env->next;
    }
    return (EXIT_SUCCESS); // fallback shouldnt happen.
}
// invalid identifier

static bool only_equals(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '=' )
            return (false);
        i++;
    }
    return (true);
}

static bool valid_first_char(char c)
{
    if (c >= 'a' && c <= 'z')
        return (true);
    if (c >= 'A' && c <= 'Z')
        return (true);
    if (c == '_')
        return (true);
    return (false);
}

static bool valid_char(char c)
{
    if (c >= 'a' && c <= 'z')
        return (true);
    if (c >= 'A' && c <= 'Z')
        return (true);
    if (c >= '0' && c <= '9')
        return (true);
    if (c == '_' || c == '=' || c == '+')
        return (true);
    return (false);
}

static bool is_printable(char c)
{
    if (c == '=')
        return (false);
	if (c >= 32 && c <= 126 || c == '\0')
	{
		return (true);
	}
	return (false);
}

static bool valid_identifier(char *str)
{
    int     i;
    bool    standalone;

    i = 0;
    standalone = true;
    if (!valid_first_char(str[i]))
        return (false);
    i++;
    while (str[i])
    {
        if (!valid_char(str[i]))
            return (false);
        else
        {
            if (str[i] == '=' || str[i] == '+')
            {
                standalone = false;
                break ;
            }
        }
        i++;
    }
    if (standalone)
        return (true);
    else
    {
        if (str[i] == '+' && str[i + 1] != '=')
            return (false);
        if (str[i] == '=' && !is_printable(str[i + 1]))
            return(false);
    }
    return (true);
}
// --------------------


static char *get_append_key(char *str)
{
    int     equals;
    bool    has_equal;
    char    *key;

    if (!str)
        return (perror("NULL Key in envp."), NULL); // cant ever happen unless i pass it.
    equals = 0;
    has_equal = false;
    while (str[equals])
    {
        if (str[equals++] == '+')
        {
            has_equal = true;
            break ;
        }
    }
    if (has_equal)
        key = ft_substr(str, 0, equals - 1); // if this fails it will return a NULL.
    else
        key = ft_strdup(str);
    return (key);
}

// kayjib key 7ed = so b+ is the key and doenst find it using strcmp
static int  append_value(char *new_var, t_envlist *env)
{
    char    *key;
    char    *value;
    char    *old_value;

    key = get_append_key(new_var);
    if (!key)
        return (EXIT_FAILURE);
    value = get_value(new_var);
    if (!value)
        return (free(key), EXIT_FAILURE);
    while (env)
    {
        if (ft_strcmp(key, env->variable) == 0)
        {
            old_value = env->value;
            env->value = ft_strjoin(old_value, value);
            free(value);
            free(old_value);
            env->exported = EXPORTED;
            return (free(key), EXIT_SUCCESS);
        }
        env = env->next;
    }
    return (EXIT_SUCCESS); // fallback shouldnt happen.
}


// function entry.
int o_export(t_tree *node, t_data *data)
{
    int         argc;
    t_envlist   *export_lst;
    int         i;

    argc = arg_count(node->argv);
    export_lst = NULL;
    if (sort_list(&export_lst, data->env) != EXIT_SUCCESS) // copy and sort list; sorted version.
            return (EXIT_FAILURE);
    i = 1;
    if (argc == 1) // only export case.
        print_export_list(export_lst);
    else
    {
        while (node->argv[i])
        {
            if (!valid_identifier(node->argv[i]))
            {
                dprintf(2, "Master@Mind: export: `%s': not a valid identifier\n", node->argv[i]);
                i++;
                continue ;
            }
            if (already_exported(node->argv[i], data))
            {
                if(has_plus(node->argv[i]))
                    append_value(node->argv[i], data->env); // check for fail
                else if (has_equal(node->argv[i]))
                    assign_new_value(node->argv[i], data->env); // check for fail.
            }
            else
            {
                if (has_equal(node->argv[i]))
                {
                    if(has_plus(node->argv[i]))
                        append_value(node->argv[i], data->env); // check for fail
                    else
                        add_to_envlist(&data->env, node->argv[i], EXPORTED); // check for failure.
                }
                else
                    add_to_envlist(&data->env, node->argv[i], NO_VALUE); // check for failure.
            }
            i++;
        }
    }
    return (free_exp_list(export_lst), EXIT_SUCCESS);
}

// when export is called
// export with no arguments
//    --> lists export list.
// export with arguments, we loop over the args
//      --> if includes '=' whe add to the env list.
//      --> exoported flag true
//      --> else false