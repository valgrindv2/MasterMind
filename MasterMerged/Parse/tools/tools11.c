/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:51:08 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/22 23:28:58 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_arglist(t_arg **arg)
{
	t_arg	*temp;

	temp = NULL;
	while ((*arg) != NULL)
	{
		free(temp);
		free((*arg)->value);
		temp = (*arg);
		if ((*arg)->next == NULL)
		{
			free(temp);
			break ;
		}
		(*arg) = (*arg)->next;
	}
}

void	cleaner_arg(t_token *list)
{
	while (list != NULL)
	{
		if (list->arg != NULL)
			clean_arglist(&list->arg);
		list = list->next;
	}
}

void	clean_yard(t_token **yard, int mode)
{
	if (mode == FAIL)
	{
		clean_fd(*yard);
		cleaner_red(*yard);
		cleaner_arg(*yard);
		list_cleaner(yard);
	}
	else if (mode == CLEAN)
		list_cleaner(yard);
}

void	clean_id_class(t_token **id_class, int mode)
{
	if (mode == FAIL)
	{
		clean_fd(*id_class);
		cleaner_red(*id_class);
		cleaner_arg(*id_class);
		list_cleaner(id_class);
	}
	else if (mode == CLEAN)
	{
		clean_fd(*id_class);
		list_cleaner(id_class);
	}
}
