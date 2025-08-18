/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:52:54 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 15:52:54 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static char	*get_last_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (ft_strdup(argv[i - 1]));
}

int	_env(t_envlist *env, char *last_cmd)
{
	t_envlist	*curr;
	char		*temp;

	curr = env;
	while (curr)
	{
		if (ft_strcmp("_", curr->variable) == 0)
		{
			temp = ft_strdup(last_cmd);
			if (!temp)
				return (EXIT_FAILURE);
			free(curr->value);
			curr->value = temp;
			return (EXIT_SUCCESS);
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int	add_last_executed(t_tree *node, t_data *data)
{
	data->last_executed = allocate_gc(get_last_argv(node->argv));
	_env(data->env, data->last_executed);
	if (_env(data->env, data->last_executed) != EXIT_SUCCESS)
		return (mind_free_all(PANIC), EXIT_FAILURE);
	data->last_executed = NULL;
	return (EXIT_SUCCESS);
}
