/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:59:36 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/04 01:59:38 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mark_unmarked(t_token *id_class)
{
	int		x;
	t_token	*curr;

	x = 0;
	curr = id_class;
	while (curr != NULL)
	{
		if (curr->op_case && curr->cmd_up_next == false)
			x = F;
		else if (curr->op_case && curr->cmd_up_next == true)
			x = 0;
		if (x == F)
			curr->in_acc = true;
		curr = curr->next;
	}
}

void	command_alone(t_token *id_class)
{
	int		x;
	t_token	*fcmd;
	t_token	*curr;

	x = 0;
	fcmd = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == COMMAND_ID)
			fcmd = curr;
		if (curr->op_case && x == 0)
		{
			if (fcmd)
				fcmd->in_acc = true;
		}
		if (red_checks(curr))
			x = F;
		curr = curr->next;
	}
}

void	file_alone(t_token *id_class)
{
	int		x;
	t_token	*file;
	t_token	*curr;

	x = 0;
	file = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		if (red_checks(curr))
			file = curr;
		if (curr->op_case && x == 0)
		{
			if (file)
				file->in_acc = true;
		}
		if (curr->tok == COMMAND_ID)
			x = F;
		curr = curr->next;
	}
}

void	command_ahead(t_token *id_class)
{
	t_token	*op;
	t_token	*curr;

	op = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		if (curr->op_case)
			op = curr;
		if (curr->tok == COMMAND_ID)
		{
			if (op)
				op->cmd_up_next = true;
		}
		curr = curr->next;
	}
	command_alone(id_class);
	file_alone(id_class);
	mark_unmarked(id_class);
}

t_token	*get_file(t_token *id_class)
{
	while (id_class != NULL)
	{
		if (red_checks(id_class)
			&& id_class->in_acc == false)
			return (id_class);
		id_class = id_class->next;
	}
	return (NULL);
}
