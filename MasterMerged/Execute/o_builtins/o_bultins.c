#include "../execute.h"


bool    validate_builtin(char *str)
{
    if (ft_strcmp(str, "echo") == 0)
        return (true);
    else if (ft_strcmp(str, "cd") == 0)
        return (true);
    else if (ft_strcmp(str, "pwd") == 0)
        return (true);
    else if (ft_strcmp(str, "export") == 0)
        return (true);
    else if (ft_strcmp(str, "unset") == 0)
        return (true);
    else if (ft_strcmp(str, "env") == 0)
        return (true);
    else if (ft_strcmp(str, "exit") == 0)
        return (true);
    return (false);
}

int exec_builtin(t_tree *node, t_data *data)
{
        if (ft_strcmp(node->argv[0], "echo") == 0)
            return (o_echo(node));
        else if (ft_strcmp(node->argv[0], "cd") == 0)
            return (o_cd(node, data), -1);
        else if (ft_strcmp(node->argv[0], "pwd") == 0)
            return (o_pwd(node, data));
        else if (ft_strcmp(node->argv[0], "export") == 0)
            return (o_export(node, data));
        else if (ft_strcmp(node->argv[0], "unset") == 0)
            return (o_unset(node, data));
        else if (ft_strcmp(node->argv[0], "env") == 0)
            return (o_env(node, data));
        else if (ft_strcmp(node->argv[0], "exit") == 0)
            return (o_exit(node, data));
    return (EXIT_SUCCESS);
}
