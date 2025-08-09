#include "../execute.h"

char *get_value(char *str)
{
    int     equals;
    bool    has_equal;
    char    *value;
    char    anon[2];

    if (!str)
        return (perror("NULL Key in envp."), NULL);
    equals = 0;
    has_equal = false;
    anon[0] = (char)127;
    anon[1] = '\0';
    while (str[equals])
    {
        if (str[equals++] == '=')
        {
            has_equal = true;
            break ;
        }
    }
    if (has_equal)
        value = ft_substr(str, equals, o_ft_strlen(str));
    else
        value = ft_strdup(anon);
    return (value);
}

char *get_key(char *str)
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
        if (str[equals++] == '=')
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

int add_to_envlist(t_envlist **envlist, char *str, bool exported)
{
    t_envlist   *new_env;
    t_envlist   *curr;

    new_env = malloc (sizeof(t_envlist));
    if (!new_env)
        return (EXIT_FAILURE);
    new_env->variable = get_key(str);
    if (!new_env->variable)
        return (free(new_env), EXIT_FAILURE);
    new_env->value = get_value(str);
    if (!new_env->value)
        return (free(new_env), free(new_env->variable), EXIT_FAILURE);
    new_env->pointed = false;
    new_env->exported = exported; // comes from parent by default exported.
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

char **convert_list_to_envp(t_envlist *envlist)
{
    t_envlist   *cur;
    char        **envp;
    size_t      env_size;
    int         i;

    env_size = envlist_size(envlist);
    envp = malloc ((env_size + 1)* sizeof(char *));
    if (!envp)
    {
        // cleanup exit;
        return (NULL);
    }
    cur = envlist;
    i = 0;
    while(cur)
    {
        envp[i] = convert_node_to_str(cur);
        cur = cur->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}
