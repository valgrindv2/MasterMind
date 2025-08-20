/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:01:35 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:54 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

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

int	count_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
			count++;
		entry = readdir (dir);
	}
	closedir(dir);
	return (count);
}

char	**alloc_files(int count)
{
	char	**files;

	if (count == 0)
		return (NULL);
	files = malloc(sizeof(char *) * (count + 1));
	if (!files)
		return (NULL);
	return (files);
}

int	init_asterisk(t_ff *ff, int count)
{
	ff->files = alloc_files(count);
	if (!ff->files)
		return (0);
	ff->dir = opendir(".");
	if (!ff->dir)
		return (free(ff->files), 0);
	return (1);
}
