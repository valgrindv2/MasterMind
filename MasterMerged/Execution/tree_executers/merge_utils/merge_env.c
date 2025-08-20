/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:27:44 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:26:51 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

size_t	no_value_nodes_num(t_envlist *env)
{
	size_t	num;

	num = 0;
	while (env)
	{
		if (!env->exported)
			num++;
		env = env->next;
	}
	return (num);
}

int	add_to_envlist(t_envlist **envlist, char *str, bool exported)
{
	t_envlist	*new_env;
	t_envlist	*curr;

	new_env = malloc(sizeof(t_envlist));
	if (!new_env)
		return (EXIT_FAILURE);
	new_env->variable = env_get_key(str);
	if (!new_env->variable)
		return (free(new_env), EXIT_FAILURE);
	new_env->value = env_get_value(str);
	if (!new_env->value)
		return (free(new_env), free(new_env->variable), EXIT_FAILURE);
	new_env->pointed = false;
	new_env->exported = exported;
	new_env->next = NULL;
	if (!*envlist)
		*envlist = new_env;
	else
	{
		curr = *envlist;
		while (curr->next)
			curr = curr->next;
		curr->next = new_env;
	}
	return (EXIT_SUCCESS);
}

char	**convert_list_to_envp(t_envlist *curr_env, t_data *data)
{
	char		**envp;
	size_t		env_size;
	int			i;

	env_size = envlist_size(curr_env) - no_value_nodes_num(curr_env);
	envp = malloc((env_size + 1) * sizeof(char *));
	if (!envp)
		return (free_argv(data->env_vec), NULL);
	i = 0;
	while (curr_env)
	{
		if (curr_env->exported)
		{
			envp[i] = convert_node_to_str(curr_env);
			if (!envp[i++])
			{
				while (--i >= 0)
					free(envp[i]);
				return (free(envp), free_argv(data->env_vec), NULL);
			}
		}
		curr_env = curr_env->next;
	}
	return (envp[i] = NULL, free_argv(data->env_vec), envp);
}
