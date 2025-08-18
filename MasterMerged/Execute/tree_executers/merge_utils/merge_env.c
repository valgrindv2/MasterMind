#include "../../execute.h"

size_t no_value_nodes_num(t_envlist *env)
{
    size_t  num;

    num = 0;
    while (env)
    {
        if (!env->exported)
            num++;
        env = env->next;
    }
    return (num);
}

char *get_value(char *str)
{
    int     equals;
    bool    has_equal;
    char    *value;

    if (!str)
        return (perror("NULL Key in envp."), NULL);
    equals = 0;
    has_equal = false;
    while (str[equals])
    {
        if (str[equals++] == '=')
        {
            has_equal = true;
            break ;
        }
    }
    if (has_equal)
        value = allocate_gc(ft_substr(str, equals, o_ft_strlen(str)));
    else
        value = allocate_gc(ft_strdup(""));
    return (value);
}

char *get_key(char *str)
{
    int     equals;
    bool    has_equal;
    char    *key;

    if (!str)
        return (perror("NULL Key in envp."), NULL);
    equals = 0;
    has_equal = false;
        while (str[equals])
    {
        if (str[equals] == '+' || str[equals] == '=')
        {
                has_equal = true;
                break;
        }
        equals++;
    }
    if (has_equal)
        key = allocate_gc(ft_substr(str, 0, equals));
    else
        key = allocate_gc(ft_strdup(str));
    return (key);
}

int add_to_envlist(t_envlist **envlist, char *str, bool exported)
{
    t_envlist   *new_env;
    t_envlist   *curr;

    new_env = allocate_gc(malloc (sizeof(t_envlist)));
    new_env->variable = get_key(str);
    new_env->value = get_value(str);
    new_env->pointed = false;
    new_env->exported = exported;
    new_env->next = NULL;
    if (!*envlist)
        *envlist = new_env;
    else
    {
        curr = *envlist;
        while (curr->next)
            curr = curr->next;
        curr->next = new_env;
    }
    return (EXIT_SUCCESS);
}

char **convert_list_to_envp(t_envlist *curr_env, t_data *data)
{
    char        **envp;
    size_t      env_size;
    int         i;

    env_size = envlist_size(curr_env) - no_value_nodes_num(curr_env);
    envp = allocate_gc(malloc ((env_size + 1)* sizeof(char *)));
    i = 0;
    while(curr_env)
    {
        if (curr_env->exported)
            envp[i] = convert_node_to_str(curr_env);
        curr_env = curr_env->next;
    }
    return (envp[i] = NULL, envp);
}
