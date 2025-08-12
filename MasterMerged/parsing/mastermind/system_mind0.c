/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_mind0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:28:08 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/12 18:54:16 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*build_tree(t_token *id_class)
{
	t_tree	*tree;
	t_token	*yard;

	tree = NULL;
	yard = NULL;
	if (id_class == NULL)
		return (NULL);
	yard = shunting_yard_algorithm(id_class); // NO_LEAKS
	if (!yard)
		return (printf("YARD FAILED\n"), clean_id_class(&id_class, FAIL), NULL);
	clean_id_class(&id_class, CLEAN);
	if (recursive_build(yard, &tree) == ANOMALY)
		return (tree_cleaner(&tree), clean_yard(&yard, FAIL), NULL);
	// read_files(yard, 0, "YARD ----->");
	print_tree(tree);
	clean_yard(&yard, CLEAN); // CLEAN BLAST FAIL
	return (tree);
}

static int	init_tree(t_tree **node)
{
	*node = malloc(sizeof(t_tree));
	// *node = NULL;
	if (!*node) // NO_LEAKS
		return (puts("INIT_TREE FAILED"), ANOMALY); // CHECK THIS ONE EHOOOO !!!!!!!! :)
	(*node)->value = NULL;
	(*node)->left = NULL;
	(*node)->right = NULL;
	(*node)->arg = NULL;
	(*node)->red = NULL;
	(*node)->argv = NULL;
	(*node)->was_s_quote = 0;
	(*node)->was_d_quote = 0;
	(*node)->fake = false;
	(*node)->op_case = 0;
	return (1);
}

static t_token	*last_unchecked(t_token *yard)
{
	t_token	*curr;

	curr = yard;
	while (curr != NULL)
	{
		if (curr->next && curr->next->marked)
			return (curr);
		curr = curr->next;
	}
	return (ft_lstlast(yard));
}

static int	put_token(t_tree *tree, t_token *token)
{
	tree->value = ft_strdup(token->identity);
	// tree->value = NULL;
	if (!tree->value) // NO_LEAKS
		return (puts("PUT_TOKEN FAILED"), ANOMALY);
	tree->tok = token->tok;
	tree->op_case = token->op_case;
	tree->red = token->red;
	tree->fake = token->fake;
	tree->was_s_quote = token->was_single_quote;
	tree->was_d_quote = token->was_double_quote;
	tree->arg = token->arg;
	token->marked = true;
	return (1);
}

int	recursive_build(t_token *yard, t_tree **tree)
{
	t_token	*token;

	if (init_tree(tree) == ANOMALY)
		return (ANOMALY);
	token = last_unchecked(yard);
	if (put_token(*tree, token) == ANOMALY)
		return (ANOMALY);
	if (token->op_case)
	{
		if (recursive_build(yard, &(*tree)->right) == ANOMALY
			|| recursive_build(yard, &(*tree)->left) == ANOMALY)
			return (ANOMALY);
	}
	else
		return (1);
	return (0);
}
