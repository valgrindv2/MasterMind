/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:07:09 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:59 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

int	o_env(t_tree *node, t_data *data)
{
	t_envlist	*curr;

	if (node->argv[1])
	{
		puterror("Master@Mind: env: does not support args\n");
		return (EXIT_FAILURE);
	}
	curr = data->env;
	while (curr != NULL)
	{
		if (curr->exported && curr->value)
		{
			printf(YLW"%s", curr->variable);
			printf(RED"=%s"RST"\n", curr->value);
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
