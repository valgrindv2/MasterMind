/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:39:40 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/06 07:20:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	con_verifications(t_token *id_class, int i)
{
	if ((id_class->tok == HERE_DOC_ID && id_class->next
			&& id_class->next->tok != DEL_ID)
		|| ((id_class->tok == PIPE_ID || id_class->tok == AND_ID
				|| id_class->tok == OR_ID)
			&& id_class->next->tok == HERE_DOC_ID && i != 0))
		return (1);
	return (0);
}

static t_token	*extract_list(t_token *id_class, t_data *data)
{
	int			i;
	t_token		*id;
	t_token		*extract;

	i = 0;
	id = NULL;
	extract = NULL;
	while (id_class != NULL)
	{
		if (con_verifications(id_class, i))
			break ;
		id = add_identity(ft_strdup(id_class->identity),
				id_class->tok, D_INIT, NULL);
		if (!id)
		{
			data->fail = 1;
			return (NULL);
		}
		add_back_identity(&extract, id, D_INIT);
		id_class = id_class->next;
		i++;
	}
	return (extract);
}

int	sef_doc(t_token *id_class, t_data *data, int mode)
{
	t_token	*class;
	t_token	*new_class;

	new_class = extract_list(id_class, data);
	if (!new_class && data->fail == 1)
		return (data->fail = 0, 0);
	else if (!new_class && data->fail == 0)
		return (1);
	set_ops(new_class);
	if (!syntax_verify(new_class, data, mode))
	{
		list_cleaner(&new_class);
		return (0);
	}
	list_cleaner(&new_class);
	return (1);
}

void	clean_stacks(t_token **stackone, t_token **stacktwo)
{
	list_cleaner(stackone);
	list_cleaner(stacktwo);
}
