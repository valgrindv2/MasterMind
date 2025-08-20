/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:27:56 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:20 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

static int	create_envlist(t_envlist **envlist, char **envp)
{
	int	i;

	i = 0;
	*envlist = NULL;
	while (envp[i])
	{
		if (add_to_envlist(envlist, envp[i++], EXPORTED)
			!= EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	tree_traverser(t_tree *root, t_data *data, size_t *recurs_count)
{
	if (*recurs_count == RECURS_LIMIT)
		return (EXIT_FAILURE);
	(*recurs_count)++;
	if (root->tok == COMMAND_ID)
		return (EXIT_SUCCESS);
	if (root->left)
	{
		if (tree_traverser(root->left, data, recurs_count) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (root->right)
	{
		if (tree_traverser(root->right, data, recurs_count) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	merge_env(t_data *data, char **env)
{
	if (data->env_is_set)
		return (EXIT_SUCCESS);
	if (create_envlist(&data->env, env) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	set_env(data->env);
	data->env_vec = convert_list_to_envp(data->env, data);
	if (!data->env_vec)
		return (mind_free_all(PANIC), EXIT_FAILURE);
	set_env_vec(data->env_vec);
	data->env_is_set = true;
	return (EXIT_SUCCESS);
}

int	merger(t_tree *root, t_data *data, char **env)
{
	static size_t	r_c;

	if (merge_env(data, env) != EXIT_SUCCESS)
		return (perror("Failed To Merge ENV"), EXIT_FAILURE);
	data->head = root;
	if (tree_traverser(root, data, &r_c) != EXIT_SUCCESS)
	{
		r_c = 0;
		return (perror("Recursion Limit"), EXIT_FAILURE);
	}
	r_c = 0;
	return (EXIT_SUCCESS);
}
