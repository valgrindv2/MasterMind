/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree_adrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:26:24 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static void	add_arg_list_to_gc(t_arg *arg)
{
	while (arg)
	{
		if (arg->value)
			allocate_gc(arg->value);
		allocate_gc(arg);
		arg = arg->next;
	}
}

static void	add_red_list_to_gc(t_red *red)
{
	while (red)
	{
		if (red->value)
			allocate_gc(red->value);
		allocate_gc(red);
		red = red->next;
	}
}

static void	add_double_str_to_gc(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		allocate_gc(arr[i++]);
	allocate_gc(arr);
}

void	tree_gc_collector(t_tree *node)
{
	if (!node)
		return ;
	if (node->value)
		allocate_gc(node->value);
	add_double_str_to_gc(node->argv);
	add_arg_list_to_gc(node->arg);
	add_red_list_to_gc(node->red);
	allocate_gc(node);
	tree_gc_collector(node->left);
	tree_gc_collector(node->right);
}

int	pipe_child_free(int ret)
{
	t_mind_alloc	**head;
	t_mind_alloc	*tmp;
	t_tree			**tree;
	t_envlist		**env;

	tree = get_tree();
	clean_tree_fds(*tree);
	close_io();
	head = get_head();
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = tmp;
	}
	*get_head() = NULL;
	env = get_env();
	free_envlist(*env);
	free(*get_pwd_reserve());
	free_argv(*get_env_vec());
	return (ret);
}
