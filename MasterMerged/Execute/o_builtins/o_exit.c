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

static long	warn_exit(const char *str)
{
	size_t		i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (EXIT_OVER_LIMIT);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (MAX_FLOW);
}

void    numeric_value(char *str, int in_parent)
{
    if (!ifnumber(str) || warn_exit(str) == EXIT_OVER_LIMIT)
    {
        if (in_parent)
            printf("exit\n");
        puterror("Master@Mind: Exit Requires A Numeric Value\n");
        exit(255);
    }
}

// function entry.

// WE NEED A FLAG TO KNOW WHETHER WE ARE IN A CHILD OR NOT
int o_exit(t_tree *node, t_data *data)
{
    char **argv;
    int in_parent;
    long exit_call;

    argv = node->argv;
    in_parent = isatty(STDIN_FILENO); // TO CHANGE
    if (count_args(argv) == 11)
        exit(data->exit_status);
    numeric_value(argv[1], in_parent);
    if (!count_args(argv))
    {
        if (in_parent)
            printf("exit\n");
        puterror("exit: too many arguments\n");
        return (1);
    }
    if (in_parent)
        printf("exit\n");
    exit_call = ft_atol(argv[1]);
    exit(exit_call);
    return (EXIT_SUCCESS);
}
/*
    exit exclusevely will be in a child only if its piped, otherwhise its executed in the parent, 
    and as u saw there a t_data *data struct, we can save a boolean flag, and mark it as true, 
    in the last step before the parent fork the exit child in the pipe, 
    this way the exit child will inherit the data struct boolean variable, 
    and we will check for it, and remove the isatty logic, 
*/