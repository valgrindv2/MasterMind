#include "../execute.h"

static int ifnumber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!('0' <= str[i] && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

static int count_args(char **argv)
{
    int i;

    i = 1;
    while (argv[i])
    {
        i++;
        if (i > 2)
            return (0);
    }
    if (i == 1)
        return (11);
    return (1);       
}

// function entry.
int o_exit(t_tree *node, t_data *data)
{
    long exit_call;
    int in_parent;


    char **argv = node->argv;
    if (!count_args(argv))
    {
        printf("exit\n");
        puterror("exit: too many arguments\n");
        return (1);
    }
    in_parent = isatty(STDIN_FILENO);
    if (in_parent)
        printf("exit\n");
    if (count_args(argv) == 11)
        exit(data->exit_status);
    if (!ifnumber(argv[1]))
    {
        puterror("Master@Mind: Exit Requires A Numeric Value\n");
        exit(255);
    }
    // exit(data->exit_status);
    exit_call = ft_atol(argv[1]);
    // if (exit_call == ANOMALY)
    // {
    //     printf("Master@mind: exit: %s: numeric argument required\n", argv[0]);
    //     exit(2);
    // }
    // printf("exit call >> %ld\n", exit_call);
    exit(exit_call);
    return (EXIT_SUCCESS);
}
