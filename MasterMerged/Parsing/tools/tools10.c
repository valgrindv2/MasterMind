/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:50:06 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/03 20:50:07 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_cleaner(t_token **list)
{
	t_token	*temp;

	temp = NULL;
	while ((*list) != NULL)
	{
		free(temp);
		free((*list)->identity);
		temp = (*list);
		if ((*list)->next == NULL)
		{
			free(temp);
			break ;
		}
		(*list) = (*list)->next;
	}
}

static void	clean_redlist(t_red **red)
{
	t_red	*temp;

	temp = NULL;
	while ((*red) != NULL)
	{
		free(temp);
		free((*red)->value);
		temp = (*red);
		if ((*red)->next == NULL)
		{
			free(temp);
			break ;
		}
		(*red) = (*red)->next;
	}
}

void	cleaner_red(t_token *list)
{
	while (list != NULL)
	{
		if (list->red != NULL)
			clean_redlist(&list->red);
		list = list->next;
	}
}

void	clean_fd(t_token *id_class)
{
	while (id_class != NULL)
	{
		if (id_class->tok == DEL_ID
			&& id_class->here_doc_fd != -1)
			close(id_class->here_doc_fd);
		id_class = id_class->next;
	}
}
