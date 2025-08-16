/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 07:25:32 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:26:04 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	push_token(t_token **br)
{
	t_token	*in;

	in = add_identity(ft_strdup("("), BRACE_O_ID, D_INIT, NULL);
	if (!in)
		return (0);
	add_back_identity(br, in, D_INIT);
	return (1);
}

int	operations_braces(char *braces, t_data *data)
{
	int		i;
	t_token	*br;

	i = 0;
	br = NULL;
	while (braces[i])
	{
		if (braces[i] == '(')
		{
			if (!push_token(&br))
				return (list_cleaner(&br), 0);
		}
		if (braces[i] == ')' && !br)
			return (data->no_sef = true, 1);
		else if (braces[i] == ')' && br)
			pop_out_brace(&br);
		i++;
	}
	if (br != NULL)
	{
		list_cleaner(&br);
		data->no_sef = true;
	}
	return (1);
}
