/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:58:42 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/03 20:59:49 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*get_argument(t_token *id_class)
{
	while (id_class != NULL)
	{
		if (id_class->op_case)
			return (NULL);
		if ((id_class->tok == ARG_ID && id_class->marked == false))
		{
			id_class->marked = true;
			return (id_class);
		}
		id_class = id_class->next;
	}
	return (NULL);
}

static void	delete_args(t_token *id_class)
{
	t_token	*temp;
	t_token	*curr;
	t_token	*before;

	before = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == ARG_ID && curr->marked == true)
		{
			before->next = curr->next;
			curr->marked = false;
			free(curr->identity);
			free(curr);
			break ;
		}
		before = curr;
		curr = curr->next;
	}
}

static int	operations(t_token *id_class)
{
	t_arg	*new;
	t_token	*arg;

	arg = get_argument(id_class);
	if (!arg)
	{
		add_arg_to_list(&id_class->arg, new_argument(id_class));
		return (1);
	}
	new = new_argument(arg);
	if (!new)
		return (0);
	if (id_class->cmd_added == false)
	{
		add_arg_to_list(&id_class->arg, new_argument(id_class));
		id_class->cmd_added = true;
	}
	add_arg_to_list(&id_class->arg, new);
	return (1);
}

int	arg_system(t_token *id_class)
{
	char	*temp;
	t_token	*temp2;
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == COMMAND_ID)
		{
			if (!operations(curr))
				return (0);
		}
		delete_args(id_class);
		if (curr->next && curr->next->tok == ARG_ID)
			continue ;
		curr = curr->next;
	}
	return (1);
}
