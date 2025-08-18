#include "../execute.h"

void	sort_files(char **files)
{
	int		i;
	int		j;
	char	*tmp;
	int		n;

	if (!files)
		return ;
	n = arg_count(files);
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(files[j], files[j + 1]) > 0)
			{
				tmp = files[j];
				files[j] = files[j + 1];
				files[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	try_expand_wildcard(t_arg *arg)
{
	if (arg->was_s_quote)
		return (EXIT_SUCCESS);
	if (arg->was_d_quote)
		return (EXIT_SUCCESS);
	if (!ft_strchr(arg->value, '*') || ft_strcmp(arg->value, "*"))
		return (EXIT_SUCCESS);
	if (expand_star_in_arg(arg) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	count_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return (count);
}
