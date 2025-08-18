/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:16:04 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 15:16:04 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	delete_node(t_envlist **env, t_envlist *to_delete)
{
	t_envlist	*curr;
	t_envlist	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (curr == to_delete)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			delete(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	unset_node(char *argument, t_envlist **env)
{
	t_envlist	*curr;

	if (!*env || ft_strcmp(argument, "_") == 0)
		return ;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(argument, curr->variable) == 0)
		{
			delete_node(env, curr);
			break ;
		}
		curr = curr->next;
	}
}

int	o_unset(t_tree *node, t_data *data)
{
	size_t	argc;
	int		i;

	data->unset_status = false;
	argc = arg_count(node->argv);
	if (argc == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (node->argv[i])
	{
		if (!valid_identifier_un(node->argv[i]))
		{
			puterror("Master@Mind: Unset: Invlid Identifier\n");
			i++;
			data->unset_status = true;
			data->exit_status = 1;
		}
		if (!node->argv[i])
			break ;
		unset_node(node->argv[i], &data->env);
		i++;
	}
	if (data->exit_status == 1 && data->unset_status == true)
		return (data->exit_status = 1, EXIT_SUCCESS);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
