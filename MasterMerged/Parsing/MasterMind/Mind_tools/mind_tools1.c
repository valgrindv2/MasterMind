/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:15:00 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/09 05:53:39 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_all_to_yard(t_token **yard, t_token **op_field)
{
	t_token	*in;
	t_token	*curr_op;

	curr_op = (*op_field);
	while (curr_op != NULL)
	{
		in = add_identity(ft_strdup(curr_op->identity),
				curr_op->tok, INIT, curr_op);
		// in = NULL; // NO_LEAKS
		if (!in)
			return (puts("ADD_ALL_TO_YARD FAILED"),S);
		add_back_identity(yard, in, D_INIT);
		curr_op = curr_op->next;
	}
	set_free(*op_field);
	(*op_field) = NULL;
	return (F);
}

static t_token	*free_set_null(t_token **op_field)
{
	t_token	*op;
	t_token	*reserve;

	op = NULL;
	reserve = NULL;
	op = add_identity(ft_strdup((*op_field)->identity),
			(*op_field)->tok, INIT, (*op_field));
	if (!op)
		return (puts("FREE_SET_NULL FAILED"), NULL); // NO_LEAKS
	if ((*op_field)->next != NULL)
		reserve = (*op_field)->next;
	free((*op_field)->identity);
	free((*op_field));
	(*op_field) = reserve;
	return (op);
}

static int	remove_last_op(t_token **yard, t_token **op_field, t_token *in)
{
	t_token	*op;

	op = free_set_null(op_field);
	if (!op)
		return (S);
	add_front_identity(op_field, in);
	add_back_identity(yard, op, D_INIT);
	return (F);
}

int	algorithm_options(t_token *curr, t_token **op_field,
		t_token **yard, t_token *in)
{
	if (((*op_field) != NULL && curr->power < (*op_field)->power)
		|| ((*op_field) != NULL && curr->power == (*op_field)->power))
	{
		if (!remove_last_op(yard, op_field, in))
			return (puts("REMOVE LAST OP FAILED"),S); // NO_LEAKS
	}
	else
		add_front_identity(op_field, in);
	return (F);
}
