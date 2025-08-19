/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:15:17 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 05:17:15 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	o_pwd(t_tree *node, t_data *data)
{
	(void)node;
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)))
		return (printf("%s\n", pwd), EXIT_SUCCESS);
	else if (data->pwd_reserve)
		return (printf("%s\n", data->pwd_reserve), EXIT_SUCCESS);
	else
		return (puterror("Getcwd Failed\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
