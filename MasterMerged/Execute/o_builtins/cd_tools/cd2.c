#include "../../execute.h"

int update_old(t_tree *node, t_data *data)
{
    char *oldpwd;

    oldpwd = get_path(data->env, P_W_D);
    if (!oldpwd)
    {
        if (change_unsetted(data->env, OLD_PWD))
            return (EXIT_SUCCESS);
    }
    else if (change_pwd(oldpwd, data->env, OLD_PWD))
        return (data->exit_status = 1, EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void check_dots(t_tree *node, int *one_dot, int *two_dot)
{
    if (ft_strnstr(node->argv[1], "..", 2))
    {
        *one_dot = 0;
        *two_dot = 1;
    }
    else if (ft_strnstr(node->argv[1], ".", 1))
        *one_dot = 1;
}

int reserve_pwd(t_tree *node, t_data *data, int one, int two)
{
    char *tmp;
    char *pwd;

    pwd = get_path(data->env, P_W_D);
    tmp = data->pwd_reserve;
    if (!pwd)
        return (EXIT_FAILURE);
    if (two && data->flag == 1)
    {
        data->pwd_reserve = ft_strjoin(data->pwd_reserve, "/..");
        free(tmp);
    }
    else if (one && data->flag == 1)
    {
        data->pwd_reserve = ft_strjoin(data->pwd_reserve, "/.");
        free(tmp);
    }
    else
    {
        free(data->pwd_reserve);
        data->pwd_reserve = ft_strdup(pwd);
    }
    if (!data->pwd_reserve)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int get_last_slash(char *pwd, int constant)
{
    int i;
    int back;

    i = o_ft_strlen(pwd) - 1;
    back = 0;
    while (i >= 0)
    {
        if (pwd[i] == '/' && (i > 0 && pwd[i - 1] != '.')) // Check only points
        {
            back = back + constant;
            while (i >= 0)
            {
                if (pwd[i] == '/')
                    back--;
                if (back == 0)
                    return (i);
                i--;
            }
        }
        else if (pwd[i] == '/')
            back++;
        i--;
    }
    return (i);
}

int dir_verify(DIR *dir, char **arg)
{
    if (!dir && !(arg[1][0] == '.' && arg[1][1] == '.'
            && arg[1][2] == '\0')
        || !dir && (arg[1][0] == '.' && arg[1][1] == '\0'))
        return (1);
    return (0);
}
