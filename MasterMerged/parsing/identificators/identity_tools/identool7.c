/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:26:47 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 06:34:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_front_identity(t_token **lst, t_token *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

t_token	*get_all_braces(t_token *token)
{
	t_token	*in;
	t_token	*braces;

	braces = NULL;
	while (token != NULL)
	{
		if (token->tok == BRACE_O_ID || token->tok == BRACE_C_ID)
		{
			in = add_identity(ft_strdup(token->identity),
					token->tok, D_INIT, NULL);
			if (!in)
				return (list_cleaner(&braces), NULL);
			add_back_identity(&braces, in, D_INIT);
		}
		token = token->next;
	}
	set_ops(braces);
	return (braces);
}

void	pop_out_brace(t_token **token)
{
	t_token	*reserve;

	if ((*token)->next != NULL)
	{
		reserve = (*token)->next;
		free((*token)->identity);
		free((*token));
		(*token) = reserve;
	}
	else
	{
		free((*token)->identity);
		free((*token));
		(*token) = NULL;
	}
}

int	push_br(t_token **stack_br, t_token *to_push)
{
	t_token	*new;

	new = add_identity(ft_strdup(to_push->identity),
			to_push->tok, D_INIT, NULL);
	if (!new)
		return (0);
	if (new->tok == BRACE_C_ID && !*stack_br)
	{
		free(new->identity);
		free(new);
		return (0);
	}
	else if (new->tok == BRACE_C_ID && (*stack_br)->tok == BRACE_O_ID)
	{
		free(new->identity);
		free(new);
		pop_out_brace(stack_br);
	}
	else
		add_back_identity(stack_br, new, D_INIT);
	return (1);
}

int	store_fd(t_token *id_class, t_data *data)
{
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == DEL_ID && curr->del_fd == false)
		{
			if (data->here_fd != -1)
				curr->here_doc_fd = dup(data->here_fd);
			if (curr->here_doc_fd == -1)
				return (close(data->here_fd), 0);
			close(data->here_fd);
			curr->del_fd = true;
			break ;
		}
		curr = curr->next;
	}
	return (1);
}
