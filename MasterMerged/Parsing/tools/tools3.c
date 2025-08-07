/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:02:56 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 03:46:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data_struct(t_data *data, char **env)
{
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
	data->env_is_set = false;
	data->check = false;
	data->pwd_reserve = NULL;
	data->chpwd = false;
	data->unreach = false;
	data->home_p = NULL;
	data->br_fail = false;
	data->pwd_reserve = NULL;
}
