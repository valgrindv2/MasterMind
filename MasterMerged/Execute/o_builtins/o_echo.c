#include "../execute.h"

static void ft_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

static bool validate_echo_option(char *str)
{
    int j;

    j = 0;
    if (str[j++] != '-')
        return (false);
    while (str[j])
    {
        if (str[j] != 'n')
            return (false);
        j++;
    }
    return (true);
}


static bool echo_printer(char *str, bool first_arg)
{
    int     i;
    bool    newline;

    i = 0;
    newline = false;
    while (str[i])
    {
        if (first_arg)
        {
            newline = validate_echo_option(str);
            if (!newline)
            {
                first_arg = false;
                continue;
            }
        }
        else
            ft_putchar(str[i]);
        i++;
    }
    return (newline);
}


// function entry
int o_echo(t_tree *node)
{
    int     i;
    bool    newline;

    newline = false;
    i = 1; // start from 1 : [0) echo] [1)hello]<-- (here)  [2)world] [NULL]; 
    // echo has already been validated in teh strcmp.
    while (node->argv[i])
    {
        if (i == 1)
            newline = echo_printer(node->argv[i], true);
        else
            echo_printer(node->argv[i], false);
        if (node->argv[i + 1])
            ft_putchar(' ');
        i++;
    }
    if (!newline)
        ft_putchar('\n');

    return (EXIT_SUCCESS);
}
