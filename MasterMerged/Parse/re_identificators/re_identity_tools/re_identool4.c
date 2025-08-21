/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:57:51 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:29:08 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_red	*get_last_red(t_red *red)
{
	while (red->next != NULL)
		red = red->next;
	return (red);
}

void	add_back_red(t_red **cmd, t_red *in)
{
	if (!in || !cmd)
		return ;
	if (*cmd)
		get_last_red(*cmd)->next = in;
	else
		(*cmd) = in;
}

void	set_last_cmd(t_token *id_class)
{
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == COMMAND_ID
			&& curr->in_acc == false)
			curr->in_acc = true;
		if (curr->op_case && curr->used == false)
		{
			curr->used = true;
			break ;
		}
		curr = curr->next;
	}
}

t_red	*redirection_cop(t_token *id_class, int *fail)
{
	t_red	*new;

	if (!id_class)
		return (*fail = 0, NULL);
	new = malloc(sizeof(t_red));
	if (!new)
		return (*fail = 1, NULL);
	new->value = ft_strdup(id_class->identity);
	if (!new->value)
		return (*fail = 1, free(new), NULL);
	new->tok = id_class->tok;
	new->was_d_quote = id_class->was_double_quote;
	new->was_s_quote = id_class->was_single_quote;
	new->next = NULL;
	if (new->tok == DEL_ID && id_class->here_doc_fd != -1)
	{
		new->fd_here_doc = dup(id_class->here_doc_fd);
		if (new->fd_here_doc == -1)
			return (*fail = 1, free(new->value), free(new), NULL);
		close(id_class->here_doc_fd);
		id_class->here_doc_fd = -1;
	}
	else if (id_class->here_doc_fd == -1)
		new->fd_here_doc = -1;
	return (new);
}

t_token	*delete_red(t_token **id_class)
{
	int		x;
	t_token	*curr;
	t_token	*before;

	x = S;
	before = NULL;
	curr = *id_class;
	while (curr != NULL)
	{
		if (curr->marked)
		{
			if (x == S)
				(*id_class) = curr->next;
			else
				before->next = curr->next;
			free(curr->identity);
			free(curr);
			break ;
		}
		before = curr;
		curr = curr->next;
		x++;
	}
	return (before);
}
