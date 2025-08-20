/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:12:29 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:28:13 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	red_checks(t_token *curr)
{
	if (curr->tok == INPUT_APP_FILE_ID || curr->tok == OUTPUT_FILE_ID
		|| curr->tok == INPUT_FILE_ID || curr->tok == DEL_ID)
		return (1);
	return (0);
}

void	last_cmd(t_token *curr, int *x, int *y, t_token **cmd)
{
	if (red_checks(curr) && curr->in_acc == false)
	{
		(*x)++;
		curr->marked = true;
	}
	else if (curr->tok == COMMAND_ID && curr->in_acc == false)
	{
		(*y)++;
		*cmd = curr;
	}
}

static t_token	*get_last_cmd(t_token *id_class)
{
	int		x;
	int		y;
	t_token	*cmd;
	t_token	*curr;

	x = 0;
	y = 0;
	cmd = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		last_cmd(curr, &x, &y, &cmd);
		if (x > 0 && y == 1)
			break ;
		if (curr->op)
		{
			x = 0;
			y = 0;
		}
		curr = curr->next;
	}
	return (cmd);
}

static int	red_ops(t_token **id_class, t_token **curr, t_token *cmd, t_red *in)
{
	int	fail;

	fail = 0;
	check_set_cmd(curr, id_class);
	if (red_checks((*curr)) || (*curr)->tok == COMMAND_ID)
	{
		in = redirection_cop(get_file(*id_class), &fail);
		cmd = get_last_cmd(*id_class);
		if (cmd && in)
		{
			add_back_red(&cmd->red, in);
			check_delete(curr, id_class);
		}
		else if ((!in && fail == S) || !cmd)
		{
			if ((*curr)->next)
				(*curr) = (*curr)->next;
			else
				return (S);
		}
		else if (!in && fail == F)
			return (ANOMALY);
	}
	return (F);
}

int	red_system(t_token **id_class)
{
	t_red	*in;
	int		catch;
	t_token	*cmd;
	t_token	*curr;

	catch = 0;
	in = NULL;
	cmd = NULL;
	curr = *id_class;
	while (curr != NULL)
	{
		catch = red_ops(id_class, &curr, cmd, in);
		if (!catch)
			break ;
		else if (catch == ANOMALY)
			return (ANOMALY);
		if (red_checks(curr))
			continue ;
		curr = curr->next;
	}
	return (1);
}
