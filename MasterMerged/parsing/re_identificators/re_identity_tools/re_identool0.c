/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:55:23 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/04 22:21:14 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	identify_argument(t_token **id_class)
{
	t_token	*curr;

	curr = *id_class;
	while (curr != NULL)
	{
		if (0 <= curr->tok && curr->tok <= 10)
			break ;
		curr->tok = ARG_ID;
		curr = curr->next;
	}
}

void	cmd_arg(t_token **curr, int *string)
{
	if ((*curr)->tok == STRING_ID && !*string)
	{
		*string = 1;
		(*curr)->tok = COMMAND_ID;
	}
	else if ((*curr)->tok == STRING_ID && *string == 1)
	{
		*string = 0;
		identify_argument(curr);
	}
}

void	re_identifications(t_token *curr, int *string)
{
	if (curr->tok == RED_IN_ID)
		curr->next->tok = INPUT_FILE_ID;
	else if (curr->tok == RED_OUT_ID)
		curr->next->tok = OUTPUT_FILE_ID;
	else if (curr->tok == RED_APP_ID)
		curr->next->tok = INPUT_APP_FILE_ID;
}

void	check_set_cmd(t_token **curr, t_token **id_class)
{
	if ((*curr)->op_case)
		set_last_cmd(*id_class);
}

void	check_delete(t_token **curr, t_token **id_class)
{
	(*curr) = delete_red(id_class);
	if (!(*curr))
		(*curr) = *id_class;
}
