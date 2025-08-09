/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:26:52 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/09 05:48:59 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	algo(t_token *curr, t_token **op_field, t_token *in, t_token **yard)
{
	in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
	// printf("in in algo >> %s\n", in->identity);
	// in = NULL;
	if (!in /*NO leaks */|| !algorithm_options(curr, op_field, yard, in)) // NO_LEAKS
		return (puts("ALGO FAAILED"), clean_node(in), S);
	return (F);
}

int	add_op(t_token *curr, t_token **op_field, t_token **yard, t_token *in)
{
	in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
	// in = NULL; //NO_LEAKS
	if (!in)
		return (puts("ADD_OP FAILED"), S);
	add_front_identity(op_field, in);
	return (F);
}

int	add_n_remove(t_token *curr, t_token **op_field, t_token **yard, t_token *in)
{
	in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
	// in = NULL; //NO_LEAKS
	if (!in)
		return (puts("ADD_N_REMOVE FAILED"),S);
	add_front_identity(op_field, in);
	if (!remove_op(yard, op_field, return_op(*op_field)))
		return (S); // NO LEAKS
	return (F);
}
