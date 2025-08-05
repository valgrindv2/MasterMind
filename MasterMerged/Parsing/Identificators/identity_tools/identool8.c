/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:29:50 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/04 03:29:52 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_quotes_state(t_token *delimiter)
{
	t_token	*curr;
	t_token	*head;

	curr = delimiter;
	head = delimiter;
	while (curr != NULL)
	{
		if (curr->was_double_quote == 1)
		{
			head->was_double_quote = 1;
			break ;
		}
		else if (curr->was_single_quote == 1)
		{
			head->was_single_quote = 1;
			break ;
		}
		curr = curr->next;
	}
}
