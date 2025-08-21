/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:08:26 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/17 07:41:37 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_ops(t_token *id_class)
{
	while (id_class != NULL)
	{
		if (0 <= id_class->tok && id_class->tok <= 6)
			id_class->op = 1;
		else
			id_class->op = 0;
		if (id_class->tok == RED_OUT_ID || id_class->tok == RED_IN_ID
			|| id_class->tok == HERE_DOC_ID || id_class->tok == RED_APP_ID
			|| id_class->tok == BRACE_O_ID || id_class->tok == BRACE_C_ID)
			id_class->firsts = 1;
		else
			id_class->firsts = 0;
		if (id_class->tok == BRACE_C_ID || id_class->tok == BRACE_O_ID)
			id_class->br = 1;
		else
			id_class->br = 0;
		if (id_class->tok == PIPE_ID || id_class->tok == OR_ID
			|| id_class->tok == AND_ID)
			id_class->op_case = 1;
		else
			id_class->op_case = 0;
		id_class = id_class->next;
	}
	return (1);
}

int	identity_scraping(char *ident, enum grammar en,
		t_token *id, t_token **id_class)
{
	if (!ident)
		return (0);
	id = add_identity(ident, en, D_INIT, NULL);
	if (!id)
		return (0);
	add_back_identity(id_class, id, INIT);
	return (1);
}

static int	unification(char *input, t_data *dt,
	t_token *id, t_token **id_class)
{
	if (!first_unit(input, &dt->i, id, id_class)
		|| !sec_unit(input, &dt->i, id, id_class)
		|| !third_unit(input, &dt->i, id, id_class)
		|| !forth_unit(input, dt, id, id_class)
		|| !set_ops(*id_class))
	{
		clean_fd(*id_class);
		list_cleaner(id_class);
		*id_class = NULL;
		return (0);
	}
	set_ops(*id_class);
	return (1);
}

t_token	*get_identity(char *input, t_data *dt)
{
	t_token	*id;
	t_token	*id_class;

	dt->i = 0;
	id = NULL;
	id_class = NULL;
	while (input[dt->i])
	{
		if (!unification(input, dt, id, &id_class))
			break ;
		if (all_whitespaces(input[dt->i]) && input[dt->i] != '\0')
			continue ;
		if (!unit_call_here_doc(&id_class, input, dt))
			break ;
		unit_call_space_next(id_class, input, &dt->i);
	}
	if (!syntax_verify(id_class, dt) || list_size(id_class) >= REC_LIMIT)
	{
		if (list_size(id_class) >= REC_LIMIT)
			puterror("Master@Mind: REC_LIMIT: Might exceed recursion limit\n");
		clean_fd(id_class);
		list_cleaner(&id_class);
		id_class = NULL;
	}
	return (free(input), input = NULL, id_class);
}
