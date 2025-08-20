/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:38:25 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:01 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

char	*get_path(t_envlist *env, char *name)
{
	while (env != NULL)
	{
		if (!ft_strcmp(name, env->variable))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*handle_no_arg(t_tree *node, t_data *data)
{
	char	*home_p;

	home_p = NULL;
	if (!node->argv[1])
	{
		home_p = get_path(data->env, HOME);
		if (!home_p)
		{
			puterror("Master@Mind: cd: HOME is not set\n");
			data->exit_status = 1;
			return (data->check = true, NULL);
		}
	}
	return (home_p);
}

int	change_pwd(char *name, t_envlist *env, char *update)
{
	while (env != NULL)
	{
		if (!ft_strcmp(update, env->variable))
		{
			free(env->value);
			env->value = ft_strdup(name);
			if (!env->value)
				return (EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	change_pwd_old(char *name, t_envlist *env, char *update, int *chpwd)
{
	if (*chpwd == 0)
		return (EXIT_SUCCESS);
	while (env != NULL)
	{
		if (!ft_strcmp(update, env->variable))
		{
			free(env->value);
			env->value = ft_strdup(name);
			if (!env->value)
				return (EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	change_unsetted(t_envlist *env, char *update)
{
	while (env != NULL)
	{
		if (!ft_strcmp(update, env->variable))
		{
			free(env->value);
			env->value = ft_strdup("");
			if (!env->value)
				return (EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
