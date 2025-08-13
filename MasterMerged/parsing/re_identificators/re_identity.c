/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:54:56 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/13 17:43:39 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	remove_q(t_token *curr, int mode)
{
	char	*removed;

	if (mode == SQ)
	{
		removed = ft_strtrim(curr->identity, "\'");
		if (!removed)
			return (S);
		free(curr->identity);
		curr->identity = removed;
		curr->was_single_quote = 1;
	}
	else if (mode == DQ)
	{
		removed = ft_strtrim(curr->identity, "\"");
		if (!removed)
			return (S);
		free(curr->identity);
		curr->identity = removed;
		curr->was_double_quote = 1;
	}
	curr->tok = STRING_ID;
	return (F);
}

static int	quotes_removal(t_token *id_class)
{
	t_token	*curr;

	curr = id_class;
	while (curr != NULL)
	{
		if (curr->tok == S_QUOTE_ID)
		{
			if (!remove_q(curr, SQ))
				return (S);
		}
		else if (curr->tok == D_QUOTE_ID)
		{
			if (!remove_q(curr, DQ))
				return (S);
		}
		curr = curr->next;
	}
	return (F);
}

t_token	*re_identity(t_token *id_class)
{
	int		string;
	t_token	*curr;

	if (id_class == NULL)
		return (NULL);
	string = 0;
	curr = id_class;
	if (!quotes_removal(id_class))
		return (clean_fd(id_class), list_cleaner(&id_class), NULL);
	while (curr != NULL)
	{
		if (curr->tok == PIPE_ID || curr->tok == OR_ID
			|| curr->tok == AND_ID)
			string = 0;
		re_identifications(curr);
		cmd_arg(&curr, &string);
		curr = curr->next;
	}
	if (!fake_system(id_class))
		return (clean_id_class(&id_class, FAIL), NULL);
	return (re_builder(id_class));
}
