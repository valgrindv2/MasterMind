/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcircuit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:53:05 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:19 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

int	short_circuit_operand(t_tree *node, t_grammar operand_id, t_data *data)
{
	int	left_status;

	left_status = recursive_execution(node->left, data);
	if (operand_id == AND_ID)
	{
		if (left_status == EXIT_SUCCESS)
			return (recursive_execution(node->right, data));
		else
			return (left_status);
	}
	else if (operand_id == OR_ID)
	{
		if (left_status != EXIT_SUCCESS)
			return (recursive_execution(node->right, data));
		else
			return (left_status);
	}
	return (EXIT_FAILURE);
}

t_tree	**get_tree(void)
{
	static t_tree	*tree = NULL;

	return (&tree);
}

void	set_tree(t_tree	*node)
{
	t_tree	**tree;

	tree = get_tree();
	*tree = node;
}

static void	clean_red_list(t_red *red)
{
	if (!red)
		return ;
	while (red)
	{
		if (red->fd_here_doc != -1)
		{
			close(red->fd_here_doc);
			red->fd_here_doc = -1;
		}
		red = red->next;
	}
}

void	clean_tree_fds(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		clean_tree_fds(node->left);
	if (node->right)
		clean_tree_fds(node->right);
	if (node->red)
		clean_red_list(node->red);
}
