/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:57:05 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/12 16:05:15 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	no_command(t_token *id_class)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (id_class != NULL)
	{
		if (id_class->tok == COMMAND_ID)
			x = 1;
		if (red_checks(id_class))
			y = 1;
		id_class = id_class->next;
	}
	if (x + y > 1)
		return (1);
	return (0);
}

static void	all_cleaner(t_token **id_class, t_token **re_built)
{
	cleaner_arg(*re_built);
	cleaner_red(*re_built);
	clean_fd(*id_class);
	list_cleaner(id_class);
	clean_fd(*re_built);
	list_cleaner(re_built);
}

static int	redirection_sys(t_token **re_built, t_token **id_class)
{
	if (no_command(*re_built))
	{
		command_ahead(*re_built);
		if (red_system(re_built) == ANOMALY)
			return (0);
	}
	return (1);
}

t_token	*re_builder(t_token *id_class)
{
	t_token	*in;
	t_token	*curr;
	t_token	*re_built;

	re_built = NULL;
	curr = id_class;
	while (curr != NULL)
	{
		if (!(1 <= curr->tok && curr->tok <= 4))
		{
			in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
			if (!in)
				return (all_cleaner(&id_class, &re_built), NULL);
			add_back_identity(&re_built, in, D_INIT);
		}
		curr = curr->next;
	}
	if (!redirection_sys(&re_built, &id_class) || !arg_system(re_built))
		return (all_cleaner(&id_class, &re_built), NULL);
	clean_id_class(&id_class, CLEAN);
	return (re_built);
}
