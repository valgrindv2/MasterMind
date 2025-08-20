/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:33 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:15 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

void	free_envlist(t_envlist *env)
{
	t_envlist	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env->variable);
		free(env);
		env = tmp;
	}
}

static void	free_redir(t_red *red)
{
	t_red	*tmp;

	if (!red)
		return ;
	while (red)
	{
		tmp = red->next;
		free(red->value);
		free(red);
		red = tmp;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free (argv);
}

void	free_tree(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	free(node->value);
	free_argv(node->argv);
	free_redir(node->red);
	free(node);
}

void	clean_up(t_tree *tree, t_data *data)
{
	(void)data;
	if (tree)
	{
		free_tree(tree);
		tree = NULL;
	}
}
