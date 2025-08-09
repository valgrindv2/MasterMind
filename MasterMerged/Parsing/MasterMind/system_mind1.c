/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_mind1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:02:13 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/09 05:54:08 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_token(t_token *curr, t_token **list)
{
	t_token	*in;

	in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
	// in = NULL; // NOLEAKS
	if (!in)
		return (puts("ADD_TOKEN FAILED"), S);
	add_back_identity(list, in, D_INIT);
	return (F);
}

int	remove_op(t_token **yard, t_token **op_field, t_token *op)
{
	if (!mark_ending(*op_field, yard))
		return (S);
	set_end(op_field);
	return (F);
}

static int	operations_field(t_token *curr, t_token **op_field, t_token **yard)
{
	t_token	*in;
	t_token	*brace_op;

	in = NULL;
	if (curr->tok == BRACE_O_ID)
	{
		if (!add_op(curr, op_field, yard, in))
			return (S);
	}
	else if (curr->op_case)
	{
		if (!algo(curr, op_field, in, yard))
			return (S);
	}
	else if (curr->tok == BRACE_C_ID)
	{
		if (!add_n_remove(curr, op_field, yard, in))
			return (S);
	}
	return (F);
}

t_token	*shunting_yard_algorithm(t_token *id_class)
{
	int		brace;
	t_token	*curr;
	t_token	*yard;
	t_token	*op_field;

	brace = 0;
	yard = NULL;
	op_field = NULL;
	set_power(id_class);
	curr = id_class;
	while (curr != NULL)
	{
		if (!curr->op_case && !curr->br && !add_token(curr, &yard))
			return (list_cleaner(&op_field), clean_yard(&yard, CLEAN), NULL);
		else if ((curr->op_case || curr->br)
			&& !operations_field(curr, &op_field, &yard))
			return (list_cleaner(&op_field), clean_yard(&yard, CLEAN), NULL);
		curr = curr->next;
	}
	if (!add_all_to_yard(&yard, &op_field)) // NO_LEAKS
		return (list_cleaner(&op_field), clean_yard(&yard, CLEAN), NULL);
	return (yard);
}
