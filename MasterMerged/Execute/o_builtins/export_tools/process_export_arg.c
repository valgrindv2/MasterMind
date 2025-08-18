#include "../../execute.h"

int  assign_new_value(char *new_var, t_envlist *env)
{
    char    *key;
    char    *value;

    key = env_get_key(new_var);
    if (!key)
        return (EXIT_FAILURE);
    value = env_get_value(new_var);
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
int append_value(char *new_var, t_envlist *env)
{
    char    *key;
    char    *value;
    char    *old_value;
    t_envlist *head;

    head = env;
    key = get_append_key(new_var);
    if (!key)
        return (EXIT_FAILURE);
    value = env_get_value(new_var);
    if (!value)
        return (free(key), EXIT_FAILURE);
    while (env)
    {
        if (ft_strcmp(key, env->variable) == 0)
        {
            old_value = env->value;
            env->value = ft_strjoin(old_value, value);
            return (free(value), free(old_value),
                env->exported = EXPORTED, free(key), EXIT_SUCCESS);
        }
        env = env->next;
    }
    add_to_envlist(&head, new_var, EXPORTED); 
    return (free(key), free(value), EXIT_SUCCESS);
}

static  bool    already_exported(char *new_var, t_data *data)
{
    t_envlist   *curr;
    char        *key;

    key = env_get_key(new_var);
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

// entry function.
int process_export_arg(char *arg, t_data *data)
{
    if (!valid_identifier(arg))
    {
        dprintf(2, "Master@Mind: export: `%s': not a valid identifier\n", arg);
        data->exit_status = 1;
        data->export_status = true;
        return (EXIT_SUCCESS);
    }
    if (already_exported(arg, data))
    {
        if (process_existing_var(arg, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    else
    {
        if (process_new_var(arg, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
