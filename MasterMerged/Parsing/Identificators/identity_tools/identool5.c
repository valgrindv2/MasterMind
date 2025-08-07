/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:21:21 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 05:03:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	takeoff_quotes(t_token *tok)
{
	char	*no_quotes;

	if (tok->tok == S_QUOTE_ID)
	{
		no_quotes = ft_strtrim(tok->identity, "\'");
		if (!no_quotes)
			return (0);
		free(tok->identity);
		tok->identity = no_quotes;
		tok->was_single_quote = 1;
	}
	else if (tok->tok == D_QUOTE_ID)
	{
		no_quotes = ft_strtrim(tok->identity, "\"");
		if (!no_quotes)
			return (0);
		free(tok->identity);
		tok->identity = no_quotes;
		tok->was_double_quote = 1;
	}
	return (1);
}

int	change_id(t_token *next_heredoc, t_data *data)
{
	if (next_heredoc->op || next_heredoc->br)
	{
		syntax_error_found(next_heredoc, data);
		return (0);
	}
	if (!delimiter_next(next_heredoc, data))
	{
		if (data->fail == true)
			return (data->fail = false, 0);
	}
	else
		return (1);
	if (!takeoff_quotes(next_heredoc))
		return (0);
	next_heredoc->tok = DEL_ID;
	return (1);
}

char	*get_delimiter(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if (curr->tok == DEL_ID)
			return (curr->identity);
		curr = curr->next;
	}
	return (NULL);
}

int	get_here_times(t_token *id_class)
{
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == HERE_DOC_ID
			&& !curr->here_done)
		{
			curr->here_done = 1;
			return (curr->here_times);
		}
		curr = curr->next;
	}
	return (0);
}

int	requirements(t_token *curr, t_token *id_class, t_data *data)
{
	if (curr->next == NULL)
		return (0);
	else if (curr->tok == HERE_DOC_ID
		&& !curr->here_done && get_here_times(id_class) == 1)
	{
		data->here_case = 2;
		return (1);
	}
	return (0);
}
