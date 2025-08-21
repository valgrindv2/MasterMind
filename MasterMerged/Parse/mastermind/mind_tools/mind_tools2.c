/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:25:55 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/18 07:39:18 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*return_op(t_token *op_field)
{
	while (op_field != NULL)
	{
		if (op_field->op_case)
			return (op_field);
		op_field = op_field->next;
	}
	return (NULL);
}

void	set_power(t_token *id_class, t_data *data)
{
	while (id_class != NULL)
	{
		if (id_class->tok == PIPE_ID)
		{
			data->piped = true;
			id_class->power = H_POW;
		}
		else if (id_class->tok == AND_ID
			|| id_class->tok == OR_ID)
			id_class->power = L_POW;
		id_class = id_class->next;
	}
}

static void	set_reserve(t_token **curr, t_token **reserve, t_token **tmp)
{
	if ((*curr)->next)
		(*reserve) = (*curr)->next;
	(*curr)->end = false;
	free((*tmp));
}

void	set_end(t_token **op_field)
{
	t_token	*temp;
	t_token	*curr;
	t_token	*reserve;

	temp = NULL;
	reserve = NULL;
	curr = *op_field;
	while (curr != NULL)
	{
		free(curr->identity);
		free(temp);
		temp = curr;
		if (curr->next == NULL)
		{
			free(temp);
			break ;
		}
		else if (curr->end == true)
		{
			set_reserve(&curr, &reserve, &temp);
			break ;
		}
		curr = curr->next;
	}
	(*op_field) = reserve;
}

int	mark_ending(t_token *op_field, t_token **yard)
{
	int	x;

	x = 0;
	while (op_field != NULL)
	{
		if (op_field->op_case && x == 0)
		{
			if (!add_token(op_field, yard))
				return (S);
		}
		if (op_field->tok == BRACE_O_ID)
		{
			x = 1;
			op_field->end = true;
			break ;
		}
		op_field = op_field->next;
	}
	return (F);
}
