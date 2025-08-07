/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:57:05 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/07 09:29:20 by codespace        ###   ########.fr       */
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

static void	all_cleaner(t_token **id_class, t_token **re_built, int mode)
{
	debbuger_tk(*re_built);
	if (mode == RED_ARG_CLEAN)
	{
		cleaner_arg(*id_class);
		cleaner_red(*id_class);
	}
	clean_fd(*id_class);
	list_cleaner(id_class);
	clean_fd(*re_built);
	list_cleaner(re_built);
	// cleaner_red(*re_built);
}

static int	redirection_sys(t_token **re_built, t_token **id_class)
{
	if (no_command(*re_built))
	{
		command_ahead(*re_built);
		if (red_system(re_built) == ANOMALY)
			return (puts("REDSYS FAILED"),0);
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
	printer(id_class, "IDCLASS >");
	while (curr != NULL)
	{
		if (!(1 <= curr->tok && curr->tok <= 4))
		{
			in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
			if (!in)
				return (all_cleaner(&id_class, &re_built, RED_ARG_CLEAN), NULL);
			add_back_identity(&re_built, in, D_INIT);
		}
		curr = curr->next;
	}
	if (!redirection_sys(&re_built, &id_class))
		return (all_cleaner(&id_class, &re_built,
			RED_ARG_CLEAN), NULL);
	clean_id_class(&id_class, CLEAN);
	return (re_built);
}
