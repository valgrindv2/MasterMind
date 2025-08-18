/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:56:15 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 14:56:15 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	new_wdir_t(t_tree *node, t_data *data, int *chpwd)
{
	char	path[PATH_MAX];
	int		one_dot;
	int		two_dot;

	one_dot = 0;
	two_dot = 0;
	data->flag = 0;
	if (!getcwd(path, sizeof(path)))
	{
		data->exit_status = 1;
		*chpwd = 1;
		data->flag = 1;
		puterror("Matser@Mind: Getcwd Failed\n");
	}
	if (change_pwd(path, data->env, P_W_D))
		return (data->exit_status = 1, EXIT_FAILURE);
	check_dots(node, &one_dot, &two_dot);
	if (reserve_pwd(node, data, one_dot, two_dot)
		|| change_pwd_old(data->pwd_reserve, data->env, P_W_D, chpwd))
		return (data->exit_status = 1, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	unreachable(t_tree *node, t_data *data)
{
	char	*tmp;
	char	pwd[PATH_MAX];

	if (con_check(node))
		return (0);
	tmp = node->argv[1];
	if (node->argv[1][0] == '.' && node->argv[1][1] == '\0')
		return (data->unreach = true, 0);
	else if (node->argv[1][0] == '.' && node->argv[1][1] == '.'
		&& node->argv[1][2] == '\0')
	{
		tmp = ft_substr(data->pwd_reserve, 0,
				get_last_slash(data->pwd_reserve, 4) + 1);
		if (!tmp)
			return (1);
		if (chdir(tmp) == -1)
			return (free(tmp), 0);
		free(tmp);
	}
	return (data->unreach = true, 0);
}

static int	op_dir(t_tree *node, t_data *data, int *x)
{
	DIR		*dir;
	char	*tmp;

	tmp = ft_substr(data->pwd_reserve, 0,
			get_last_slash(data->pwd_reserve, 1) + 1);
	dir = opendir(tmp);
	if (!dir)
		return (puterror("Master@Mind: Permission Denied\n"),
			free(tmp), data->exit_status = 1, EXIT_FAILURE);
	else
	{
		closedir(dir);
		free(node->argv[1]);
		node->argv[1] = tmp;
		*x = 1;
		chdir(node->argv[1]);
		data->unreach = true;
		return (EXIT_SUCCESS);
	}
}

static int	new_wdir(t_tree *node, t_data *data, int *chpwd)
{
	char	*pwd;
	DIR		*dir;
	int		x;

	x = 0;
	data->unreach = false;
	if (update_old(node, data))
		return (data->exit_status = 1, EXIT_FAILURE);
	if (chdir(node->argv[1]) == -1)
	{
		dir = opendir(node->argv[1]);
		if (dir_verify(dir, node->argv))
			return (puterror("Master@Mind: cd: Dir Or File Is Unreachable\n"),
				data->exit_status = 1, EXIT_FAILURE);
		if (op_dir(node, data, &x))
			return (EXIT_FAILURE);
		if (!x && unreachable(node, data))
			return (data->exit_status = 1, EXIT_FAILURE);
		if (data->unreach == false)
			return (puterror("Master@Mind: cd: Dir Or File Is Unreachable\n"),
				data->exit_status = 1, EXIT_FAILURE);
	}
	if (new_wdir_t(node, data, chpwd))
		return (data->exit_status = 1, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	o_cd(t_tree *node, t_data *data)
{
	int		chpwd;

	chpwd = 0;
	data->unreach = false;
	data->check = false;
	data->home_p = handle_no_arg(node, data);
	if (!data->home_p && data->check == true)
		return (EXIT_FAILURE);
	else if (data->home_p && !node->argv[1])
	{
		if (update_old(node, data))
			return (EXIT_FAILURE);
		if (chdir(data->home_p) == -1)
			return (puterror("Maste@Mind: cd: File Or Directory Not Found\n"),
				data->exit_status = 1, EXIT_FAILURE);
		if (change_pwd(data->home_p, data->env, P_W_D))
			return (EXIT_FAILURE);
		free(data->pwd_reserve);
		data->pwd_reserve = ft_strdup(data->home_p);
		if (!data->pwd_reserve)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (new_wdir(node, data, &chpwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
