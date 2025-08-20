/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:43:26 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:03 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

int	con_check(t_tree *node)
{
	if (node->argv[1][0] == '.' && node->argv[1][1] == '\0')
		return (0);
	if (node->argv[1][0] == '.' && node->argv[1][1] == '.'
		&& node->argv[1][2] == '\0')
		return (0);
	return (1);
}

char	*reserve_tool(char *pwd, t_data *data, int two, int one)
{
	char	*tmp;

	tmp = data->pwd_reserve;
	if (two && data->flag == 1)
	{
		data->pwd_reserve = ft_strjoin(data->pwd_reserve, "/..");
		free(tmp);
	}
	else if (one && data->flag == 1)
	{
		data->pwd_reserve = ft_strjoin(data->pwd_reserve, "/.");
		free(tmp);
	}
	else
	{
		free(data->pwd_reserve);
		data->pwd_reserve = ft_strdup(pwd);
	}
	if (!data->pwd_reserve)
		return (NULL);
	return (data->pwd_reserve);
}

void	init_cd_tools(t_tree *node, t_data *data, int *chpwd)
{
	*chpwd = 0;
	data->unreach = false;
	data->check = false;
	data->home_p = handle_no_arg(node, data);
}
