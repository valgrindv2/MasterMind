/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:02:23 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:57:36 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	re_init_tool(t_token *new, t_token *old)
{
	new->brace_c = old->brace_c;
	new->brace_o = old->brace_o;
	new->op_case = old->op_case;
	new->space_next = old->space_next;
	new->cmd_up_next = old->cmd_up_next;
	new->was_double_quote = old->was_double_quote;
	new->was_single_quote = old->was_single_quote;
	new->here_document_act = old->here_document_act;
	new->al_used = old->al_used;
	new->cmd_added = old->cmd_added;
	new->fake = old->fake;
	new->alre_doc = old->alre_doc;
	new->quotes_syntax = old->quotes_syntax;
}

void	init_tool(t_token *new)
{
	new->marked = false;
	new->del_fd = false;
	new->in_acc = false;
	new->here_doc_fd = -1;
	new->space_next = false;
	new->cmd_up_next = false;
	new->was_single_quote = 0;
	new->was_double_quote = 0;
	new->here_document_act = false;
	new->al_used = false;
	new->cmd_added = false;
	new->fake = false;
	new->alre_doc = false;
	new->quotes_syntax = 0;
}
