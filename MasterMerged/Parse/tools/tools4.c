/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:12:16 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:13:17 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envlist	*get_last_node(t_envlist *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

t_envlist	*add_variable_value(char *variable, char *value)
{
	t_envlist	*node;

	node = malloc(sizeof(t_envlist));
	node->variable = ft_strjoin(variable, "=");
	if (!node->variable)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_to_env(t_envlist **env, t_envlist *variable)
{
	if (*env)
		get_last_node(*env)->next = variable;
	else
		*env = variable;
}

char	*cpy_variable(char *var_place, char *variable)
{
	int	i;

	i = 0;
	var_place = malloc(get_len(variable) + 1);
	if (!var_place)
		return (NULL);
	while (variable[i])
	{
		var_place[i] = variable[i];
		i++;
	}
	var_place[i] = '\0';
	return (var_place);
}

void	panic(t_data *data, char *input)
{
	freeiers(data, input);
	exit(F);
}
