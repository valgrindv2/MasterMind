/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:41:09 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:02 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

int	update_old(t_tree *node, t_data *data)
{
	char	*oldpwd;

	(void)node;
	oldpwd = get_path(data->env, P_W_D);
	if (!oldpwd)
	{
		if (change_unsetted(data->env, OLD_PWD))
			return (EXIT_SUCCESS);
	}
	else if (change_pwd(oldpwd, data->env, OLD_PWD))
		return (data->exit_status = 1, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	check_dots(t_tree *node, int *one_dot, int *two_dot)
{
	if (ft_strnstr(node->argv[1], "..", 2))
	{
		*one_dot = 0;
		*two_dot = 1;
	}
	else if (ft_strnstr(node->argv[1], ".", 1))
		*one_dot = 1;
}

int	reserve_pwd(t_tree *node, t_data *data, int one, int two)
{
	char	*pwd;

	(void)node;
	pwd = get_path(data->env, P_W_D);
	if (!pwd)
		return (EXIT_FAILURE);
	data->pwd_reserve = reserve_tool(pwd, data, two, one);
	set_pwd(data->pwd_reserve);
	if (!data->pwd_reserve)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_last_slash(char *pwd, int constant)
{
	int	i;
	int	back;

	i = o_ft_strlen(pwd) - 1;
	back = 0;
	while (i >= 0)
	{
		if (pwd[i] == '/' && (i > 0 && pwd[i - 1] != '.'))
		{
			back = back + constant;
			while (i >= 0)
			{
				if (pwd[i] == '/')
					back--;
				if (back == 0)
					return (i);
				i--;
			}
		}
		else if (pwd[i] == '/')
			back++;
		i--;
	}
	return (i);
}

int	dir_verify(DIR *dir, char **arg)
{
	if ((!dir && !(arg[1][0] == '.' && arg[1][1] == '.'
		&& arg[1][2] == '\0'))
		|| (!dir && (arg[1][0] == '.' && arg[1][1] == '\0')))
		return (1);
	if (dir)
		closedir(dir);
	return (0);
}
