/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:02:56 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/14 21:10:51 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void init_data_tt(t_data *data)
{
	data->env_is_set = false;
	data->check = false;
	data->pwd_reserve = NULL;
	data->chpwd = false;
	data->unreach = false;
	data->home_p = NULL;
	data->br_fail = 0;
	data->pwd_reserve = NULL;
	// added.
	data->export_status = false;
	data->pid = 1111;
    data->last_executed = NULL;
	data->unset_status = false;
	data->here_read_fd = -1;
}

void	init_data_struct(t_data *data, char **env)
{
	(void)env;
	data->append = 0;
	data->to_env = 0;
	data->to_exp = 0;
	data->is_child = 0;
	data->here_minus = 0;
	data->exit_status = 0;
	data->fail = 0;
	data->i = 0;
	data->env = NULL;
	data->exp = NULL;
	data->env_vec = NULL;
	data->saved_in = -1;
	data->saved_out = -1;
	init_data_tt(data);
}

void	tree_cleaner(t_tree **node)
{
	if (!*node)
		return ;

	if ((*node)->left)
		tree_cleaner(&(*node)->left);
	if ((*node)->right)
		tree_cleaner(&(*node)->right);
	free((*node)->value);
	free((*node));
}
