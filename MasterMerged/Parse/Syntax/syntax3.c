/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:39:40 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/13 17:40:14 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		id = add_identity(ft_strdup(id_class->identity),
				id_class->tok, D_INIT, NULL);
		if (!id)
			return (data->fail = 1, NULL);
		add_back_identity(&extract, id, D_INIT);
		if (id_class->tok == DEL_ID && id_class->alre_doc == false)
		{
			id_class->alre_doc = true;
			break ;
		}
		id_class = id_class->next;
		i++;
	}
	return (extract);
}

int	sef_doc(t_token *id_class, t_data *data)
{
	t_token	*new_class;

	new_class = extract_list(id_class, data);
	if (!new_class && data->fail == 1)
		return (data->fail = 0, 0);
	else if (!new_class && data->fail == 0)
		return (1);
	set_ops(new_class);
	if (!syntax_verify(new_class, data))
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
