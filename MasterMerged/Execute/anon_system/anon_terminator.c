#include "../execute.h"

static int	anon_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ANON)
			return (i);
		i++;
	}
	return (i);
}

bool	single_anon(char *str)
{
	if (str[0] == ANON && str[1] == '\0')
		return (true);
	return (false);
}

static void	init_terminator(t_ifs **args, int *i)
{
	*args = NULL;
	*i = 0;
}

static char	*trim_anon_free(char *str)
{
	char	*cut;

	cut = allocate_gc(ft_substr(str, anon_index(str) + 1, o_ft_strlen(str)));
	return (cut);
}

char	**terminate_inside_anons(char **argv)
{
	t_ifs	*args;
	char	**new_argv;
	int		i;

	init_terminator(&args, &i);
	while (argv[i])
	{
		if (!single_anon(argv[i]))
		{
			if (still_has_anon(argv[i]))
				argv[i] = trim_anon_free(argv[i]);
			if (add_ifs_back(&args, argv[i]) != EXIT_SUCCESS)
				return (NULL);
		}
		i++;
	}
	new_argv = ifs_list_to_argv(args);
	return (new_argv);
}
