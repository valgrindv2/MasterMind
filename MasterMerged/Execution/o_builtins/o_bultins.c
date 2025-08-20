/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_bultins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:53:04 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:57 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

bool	validate_builtin(char *str)
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

int	exec_builtin(t_tree *node, t_data *data)
{
	if (ft_strcmp(node->argv[0], "echo") == 0)
		return (o_echo(node));
	else if (ft_strcmp(node->argv[0], "cd") == 0)
		return (o_cd(node, data), data->exit_status);
	else if (ft_strcmp(node->argv[0], "pwd") == 0)
		return (o_pwd(node, data));
	else if (ft_strcmp(node->argv[0], "export") == 0)
		return (o_export(node, data), data->exit_status);
	else if (ft_strcmp(node->argv[0], "unset") == 0)
		return (o_unset(node, data), data->exit_status);
	else if (ft_strcmp(node->argv[0], "env") == 0)
		return (o_env(node, data));
	else if (ft_strcmp(node->argv[0], "exit") == 0)
		return (o_exit(node, data));
	return (EXIT_SUCCESS);
}

int	**get_exit_status(void)
{
	static int	*ex = NULL;

	return (&ex);
}

void	set_exit_status(int *status)
{
	int	**exit_status;

	exit_status = get_exit_status();
	*exit_status = status;
}

int	peak_status(void)
{
	int	**exit_status;

	exit_status = get_exit_status();
	return (**exit_status);
}
