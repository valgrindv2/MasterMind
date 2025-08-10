/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:10:27 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 09:03:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	init_properties(t_token *new)
{
	new->br = 0;
	new->op = 0;
	new->end = 0;
	new->power = 0;
	new->firsts = 0;
	new->red = NULL;
	new->arg = NULL;
	new->brace_o = 0;
	new->op_case = 0;
	new->brace_c = 0;
	new->used = false;
	new->space_next = 0;
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

static void	re_initialization(t_token *new, t_token *old)
{
	new->br = old->br;
	new->op = old->op;
	new->end = old->end;
	new->red = old->red;
	new->arg = old->arg;
	new->used = old->used;
	new->power = old->power;
	new->in_acc = old->in_acc;
	new->del_fd = old->del_fd;
	new->firsts = old->firsts;
	new->marked = old->marked;
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

void	add_back_identity(t_token **lst, t_token *new, int mode)
{
	if (!new || !lst)
		return ;
	if (!ft_strcmp(new->identity, "<<"))
	{
		new->here_done = 0;
		new->here_times = 1;
	}
	if (mode == INIT)
		init_properties(new);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_token	*add_identity(char *content, enum grammar tok, int mode, t_token *infos)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!content || !new_node)
		return (free(new_node), NULL);
	new_node->identity = ft_strdup(content);
	free(content);
	if (!new_node->identity)
		return (free(new_node), NULL);
	new_node->tok = tok;
	new_node->next = NULL;
	if (mode == INIT)
	{
		re_initialization(new_node, infos);
		if (infos->here_doc_fd != -1)
		{
			new_node->here_doc_fd = dup(infos->here_doc_fd);
			if (new_node->here_doc_fd == -1)
				return (free(new_node->identity), free(new_node), NULL);
			close(infos->here_doc_fd);
		}
		else
			new_node->here_doc_fd = -1;
	}
	return (new_node);
}
