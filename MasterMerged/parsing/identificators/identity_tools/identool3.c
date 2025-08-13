/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:16:17 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/13 17:41:04 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	space_flag(t_token *id_class)
{
	t_token	*last_token;

	last_token = ft_lstlast(id_class);
	if (id_class)
		last_token->space_next = true;
}

int	all_whitespaces(char x)
{
	if ((9 <= x && x <= 13) || x == 32)
		return (0);
	return (1);
}

int	whitespaces(char x)
{
	if ((9 <= x && x <= 13) || x == 32)
		return (0);
	return (1);
}

int	unit_call_here_doc(t_token **id_class, char *input, t_data *data)
{
	(void)input;
	if (!here_doc_check(*id_class, data))
	{
		clean_fd(*id_class);
		list_cleaner(id_class);
		*id_class = NULL;
		return (0);
	}
	return (1);
}

void	unit_call_space_next(t_token *id_class, char *input, int *index)
{
	if (!whitespaces(input[*index]))
	{
		space_flag(id_class);
		(*index)++;
	}
}
