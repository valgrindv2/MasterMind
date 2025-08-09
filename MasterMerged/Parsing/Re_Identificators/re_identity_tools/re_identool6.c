/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:00:11 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/09 00:39:32 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_arg	*last_arg_node(t_arg *arg_list)
{
	while (arg_list->next != NULL)
		arg_list = arg_list->next;
	return (arg_list);
}

void	add_arg_to_list(t_arg **arg_list, t_arg *arg)
{
	if (!arg || !arg_list)
		return ;
	if (*arg_list)
		last_arg_node(*arg_list)->next = arg;
	else
		*arg_list = arg;
}

t_arg	*new_argument(t_token *new)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	if (arg)
	{
		arg->value = ft_strdup(new->identity);
		if (!arg->value)
			return (free(arg), NULL);
		arg->tok = new->tok;
		arg->was_s_quote = new->was_single_quote;
		arg->was_d_quote = new->was_double_quote;
		arg->space_next = new->space_next;
		arg->next = NULL;
	}
	return (arg);
}
