#include "../execute.h"

size_t  env_strlen(t_envlist *envlist)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (envlist->variable[i])
        i++;
    while(envlist->value[j])
        j++;
    return (i + j);
}

size_t  envlist_size(t_envlist *env)
{
    size_t  size;

    size = 0;
    while (env)
    {
        size++;
        env = env->next;
    }
    return (size);
}

char    *convert_node_to_str(t_envlist *env_node)
{
    char    *str;
    size_t  env_len;
    int     i;
    int     j;

    env_len = env_strlen(env_node);
    str = malloc (env_len + 2); // one for equal and one for null.
    if (!str)
        return (NULL);
    i = 0;
    while (env_node->variable[i])
    {
        str[i] = env_node->variable[i];
        i++;
    }
    str[i++] = '=';
    j = 0;
    while (env_node->value[j])
    {
        str[i++] = env_node->value[j++];
    }
    str[i] = '\0';
    return (str);
}