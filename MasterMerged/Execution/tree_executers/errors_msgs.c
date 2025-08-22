/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/22 23:37:33 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

void	print_errno(char *str)
{
	if (str)
		puterror(allocate_gc(ft_strjoin("Master@Mind: ", str)));
	else if (!str)
		write(2, "Error", 6);
}

int	errors_msgs(int err, char *cmd)
{
	if (err == 127)
		return (puterror("Master@Mind: command not found\n"), 127);
	if (err == 8)
		return (0);
	else if (err == 2)
	{
		if (!ft_strchr(cmd, '/'))
			return (print_errno(allocate_gc(ft_strjoin(cmd,
							" ...command not found\n"))), 127);
		else
			return (print_errno("No such file or directory\n"), 127);
	}
	else if (err == 14)
		return (print_errno("No such file or directory\n"), 127);
	else if (err == 13)
		return (print_errno("Permission denied\n"), 126);
	else if (err == 20)
		return (print_errno("Not a directory\n"), 126);
	else if (err == 22 || err == 21)
		return (puterror("Master@Mind: is a directory\n"), 126);
	return (err);
}

int	is_it_dir(char *cmd)
{
	struct stat	dir;

	if (stat(cmd, &dir) < 0)
		return (0);
	return (S_ISDIR(dir.st_mode));
}

void	close_saved(t_data *data)
{
	if (data->saved_in != -1)
	{
		close(data->saved_in);
		data->saved_in = -1;
	}
	if (data->saved_out != -1)
	{
		close(data->saved_out);
		data->saved_out = -1;
	}
}

void	exists_zero(t_tree *node, t_data *data)
{
	close_saved(data);
	print_errno(allocate_gc(ft_strjoin(node->argv[0],
				" ...command not found\n")));
	exit(pipe_child_free(127));
}
