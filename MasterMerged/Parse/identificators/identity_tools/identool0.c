/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:10:27 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/12 15:16:05 by ayel-bou         ###   ########.fr       */
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
	new->passed = false;
	init_tool(new);
}

static int	re_initialization(t_token *new, t_token *old)
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
	new->passed = old->passed;
	re_init_tool(new, old);
	if (old->here_doc_fd != -1)
	{
		new->here_doc_fd = dup(old->here_doc_fd);
		if (new->here_doc_fd == -1)
			return (free(new->identity), free(new), 0);
		close(old->here_doc_fd);
		old->here_doc_fd = -1;
	}
	else
		new->here_doc_fd = -1;
	return (1);
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
		if (!re_initialization(new_node, infos))
			return (NULL);
	}
	return (new_node);
}
