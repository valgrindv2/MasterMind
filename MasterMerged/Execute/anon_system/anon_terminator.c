#include "../execute.h"

static int anon_index(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (char)127)
            return (i);
        i++;
    }
    return (i); // fall back shouldnt happen.
}

static bool single_anon(char *str)
{
    if (str[0] == (char)127 && str[1] == '\0')
        return (true);
    return (false);
}

static void init_terminator(t_ifs **args, int *i)
{
    *args = NULL;
    *i = 0;
}

static char *trim_anon_free(char *str)
{
    char    *cut;

    cut = ft_substr(str, anon_index(str) + 1, o_ft_strlen(str));
    free(str);
    return (cut);
}

// terminator entry.
char **terminate_inside_anons(char **argv)
{
    t_ifs   *args;
    char    **new_argv;
    int     i;

    init_terminator(&args, &i);
    while (argv[i])
    {
        if (!single_anon(argv[i]))
        {
            if (still_has_anon(argv[i]))
            {
                argv[i] = trim_anon_free(argv[i]); // gets freed inside
                if (!argv[i])
                    return (free_ifs_list(args), free_argv(argv), NULL);
            }
            if (add_ifs_back(&args, argv[i]) != EXIT_SUCCESS)
                return (free_ifs_list(args), free_argv(argv), NULL);
        }
        i++;
    }
    new_argv = ifs_list_to_argv(args);
    if (!new_argv)
        return (free_ifs_list(args),  free_argv(argv), NULL);
    return(free_ifs_list(args), free_argv(argv), new_argv);
}
