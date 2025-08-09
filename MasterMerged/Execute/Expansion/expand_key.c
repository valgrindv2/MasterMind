#include "../execute.h"

static char *o_ft_strtrim(char *s, char *set)
{
    int start;
    int end;

    if (!s || !set)
        return (NULL);
    start = 0;
    // skip leading characters in 'set'
    while (s[start] && ft_strchr(set, s[start]))
        start++;
    end = o_ft_strlen(s);
    if (end == 0)
        return (ft_substr(s, 0, 0));
    end--;
    // skip trailing characters in 'set'
    while (end > start && ft_strchr(set, s[end]))
        end--;
    return (ft_substr(s, start, end - start + 1));
}

static char *trim_key_spaces(char *key)
{
    char *trimmed;

    if (!key)
        return (NULL);
    trimmed = o_ft_strtrim(key, " \t\n\v\f\r");
    if (!trimmed)
        return (NULL);
    return (trimmed);
}

static char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;
    char        *trimmed_key;
    char        anon[2];

    cur = envlist;
    trimmed_key = trim_key_spaces(key);
    if (!trimmed_key)
        return (free(key), NULL);
    free(key); 
    key = trimmed_key;
    anon[0] = (char)127;
    anon[1] = '\0';
    while (cur) 
    {
        if (ft_strcmp(key, cur->variable) == 0)
        {
            if (cur->value[0] == '\0')
                return (free(key), ft_strdup(anon));
            return (free(key), ft_strdup(cur->value)); // return value
        }
        cur = cur->next;
    }
    return (free(key), ft_strdup(anon)); // non printable to detect not passing it to execve.
}

//entry function.
char *expand_key(char *str, t_data *data, int keylen, int *i)
{
    char    *value;
    char    *key;

    key = ft_substr(str, *i + 1, keylen); // trims $ from start, free after
    *i += keylen + 1; // keylen + 1 [$]
    if (!key)
        return (NULL);
	value = find_in_env(data->env, key);
    if (!value)
        return (NULL);
    return (value);
}
