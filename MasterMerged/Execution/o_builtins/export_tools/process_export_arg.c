/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:21:57 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/23 15:49:02 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

int	assign_new_value(char *new_var, t_envlist *env)
{
	char	*key;
	char	*value;

	key = env_get_key(new_var);
	if (!key)
		return (EXIT_FAILURE);
	value = env_get_value(new_var);
	if (!value)
		return (free(key), EXIT_FAILURE);
	while (env)
	{
		if (ft_strcmp(key, env->variable) == 0)
		{
			free(env->value);
			env->value = value;
			env->exported = EXPORTED;
			return (free(key), EXIT_SUCCESS);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static char	*get_append_key(char *str)
{
	int		equals;
	bool	has_equal;
	char	*key;

	if (!str)
		return (perror("NULL Key in envp."), NULL);
	equals = 0;
	has_equal = false;
	while (str[equals])
	{
		if (str[equals++] == '+')
		{
			has_equal = true;
			break ;
		}
	}
	if (has_equal)
		key = ft_substr(str, 0, equals - 1);
	else
		key = ft_strdup(str);
	return (key);
}

int	append_value(char *new_var, t_envlist *env)
{
	char		*key;
	char		*value;
	char		*old_value;
	t_envlist	*head;

	head = env;
	key = get_append_key(new_var);
	if (!key)
		return (EXIT_FAILURE);
	value = env_get_value(new_var);
	if (!value)
		return (free(key), EXIT_FAILURE);
	while (env)
	{
		if (ft_strcmp(key, env->variable) == 0)
		{
			old_value = env->value;
			env->value = ft_strjoin(old_value, value);
			return (free(value), free(old_value),
				env->exported = EXPORTED, free(key), EXIT_SUCCESS);
		}
		env = env->next;
	}
	add_to_envlist(&head, new_var, EXPORTED);
	return (free(key), free(value), EXIT_SUCCESS);
}

static bool	already_exported(char *new_var, t_data *data)
{
	t_envlist	*curr;
	char		*key;

	key = env_get_key(new_var);
	if (!key)
		return (false);
	curr = data->env;
	while (curr)
	{
		if (ft_strcmp(key, curr->variable) == 0)
		{
			return (free(key), true);
		}
		curr = curr->next;
	}
	return (free(key), false);
}

int	process_export_arg(char *arg, t_data *data)
{
	if (!valid_identifier(arg))
	{
		perror("Master@Mind: export: Invalid Identifier\n");
		data->exit_status = 1;
		data->export_status = true;
		return (EXIT_SUCCESS);
	}
	if (already_exported(arg, data))
	{
		if (process_existing_var(arg, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (process_new_var(arg, data) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
