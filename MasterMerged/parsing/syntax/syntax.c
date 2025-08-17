/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:25:23 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/17 06:24:29 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error_found(t_token *curr, t_data *data)
{
	print_error(SYNTAX, curr->identity, SYN);
	data->exit_status = 258;
}

static int	first_and_null(t_token *curr)
{
	if (curr->op && !curr->next)
		return (F);
	if (curr->op && !curr->firsts)
		return (F);
	return (S);
}

int	hold_and_check(t_token *hold, t_token *curr)
{
	if ((hold->op && curr->op && !hold->op_case)
		|| (hold->op && curr->br && !hold->op_case)
		|| (curr->op_case && hold->op)
		|| (hold->op_case && curr->tok == BRACE_C_ID))
		return (F);
	if ((hold->tok == BRACE_O_ID && curr->op_case)
		|| (hold->op && curr->br && !hold->op_case))
		return (F);
	if ((hold->tok == STRING_ID && curr->tok == BRACE_O_ID)
		|| (hold->tok == BRACE_C_ID && curr->tok == STRING_ID)
		|| (hold->tok == BRACE_C_ID && !curr->op_case
			&& curr->tok != BRACE_C_ID)
		|| (!hold->op_case && hold->tok != BRACE_O_ID
			&& curr->tok == BRACE_O_ID))
		return (F);
	if ((hold->tok == DEL_ID && curr->tok == BRACE_O_ID)
		|| (hold->tok == BRACE_C_ID && curr->tok == DEL_ID))
		return (F);
	if (curr->op && !curr->next)
		return (F);
	return (S);
}

static int	cmp_nodes(t_token *hold, t_token *verify, t_data *data)
{
	if (hold_and_check(hold, verify))
	{
		syntax_error_found(verify, data);
		data->exit_status = 258;
		return (F);
	}
	return (S);
}

int	syntax_verify(t_token *token, t_data *data)
{
	int		i;
	t_token	*hold;
	t_token	*verify;

	i = 0;
	hold = NULL;
	verify = token;
	while (verify != NULL)
	{
		if (hold != NULL && cmp_nodes(hold, verify, data))
			return (0);
		if (i == 0 && first_and_null(verify))
		{
			syntax_error_found(verify, data);
			data->exit_status = 258;
			return (0);
		}
		hold = verify;
		verify = verify->next;
		i++;
	}
	if (scan_for_doubles(token) && !doubles_verify(token, data))
		return (data->exit_status = 258, 0);
	return (1);
}
