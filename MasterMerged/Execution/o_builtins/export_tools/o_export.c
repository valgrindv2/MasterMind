/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:10:34 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/22 23:35:11 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

static void	print_export_list(t_envlist *env)
{
	t_envlist	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->variable, "_") != 0)
		{
			printf("declare -x %s", curr->variable);
			if (curr->exported)
				printf("=\"%s\"", curr->value);
			printf("\n");
		}
		curr = curr->next;
	}
}

static void	swap_env_nodes(t_envlist *a, t_envlist *b)
{
	char	*tmp_var;
	char	*tmp_value;
	bool	tmp_exported;

	tmp_var = a->variable;
	tmp_value = a->value;
	tmp_exported = a->exported;
	a->variable = b->variable;
	a->value = b->value;
	a->exported = b->exported;
	b->variable = tmp_var;
	b->value = tmp_value;
	b->exported = tmp_exported;
}

static void	sort_operation(t_envlist **exp)
{
	t_envlist	*trav1;
	t_envlist	*trav2;

	trav1 = *exp;
	while (trav1 != NULL)
	{
		trav2 = trav1->next;
		while (trav2 != NULL)
		{
			if (ft_strcmp(trav1->variable, trav2->variable) > 0)
				swap_env_nodes(trav1, trav2);
			trav2 = trav2->next;
		}
		trav1 = trav1->next;
	}
}

static int	sort_list(t_envlist **export_lst, t_envlist *env)
{
	while (env)
	{
		if (add_to_export_list(export_lst, env) != EXIT_SUCCESS)
			return (free_exp_list(*export_lst),
				mind_free_all(PANIC), EXIT_FAILURE);
		env = env->next;
	}
	sort_operation(export_lst);
	return (EXIT_SUCCESS);
}

int	o_export(t_tree *node, t_data *data)
{
	int			argc;
	t_envlist	*export_lst;
	int			i;

	data->export_status = false;
	argc = arg_count(node->argv);
	export_lst = NULL;
	if (sort_list(&export_lst, data->env) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (argc == 1)
		print_export_list(export_lst);
	else
	{
		i = 1;
		while (node->argv[i])
		{
			if (process_export_arg(node->argv[i], data) != EXIT_SUCCESS)
				return (free_exp_list(export_lst), EXIT_FAILURE);
			i++;
		}
	}
	if (data->exit_status == 1 && data->export_status == true)
		return (free_exp_list(export_lst), data->exit_status = 1, EXIT_SUCCESS);
	return (free_exp_list(export_lst), data->exit_status = 0, EXIT_SUCCESS);
}
