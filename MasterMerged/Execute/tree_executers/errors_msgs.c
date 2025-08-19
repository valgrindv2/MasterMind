/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 15:28:06 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	print_errno(char *str)
{
	puterror("Master@Mind: ");
	if (str)
		write(2, str, o_ft_strlen(str));
	else if (!str)
		write(2, "Error", 6);
	write(2, "\n", 1);
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
							" ...command not found"))), 127);
		else
			return (print_errno("No such file or directory"), 127);
	}
	else if (err == 13)
		return (print_errno("Permission denied"), 126);
	else if (err == 20)
		return (print_errno("Not a directory"), 126);
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
