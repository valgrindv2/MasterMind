/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pocket_insertion_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:52 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

bool	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

char	*expand_special_cases(char *str, t_data *data, int *i)
{
	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (allocate_gc(o_ft_itoa(data->exit_status)));
	}
	else if (str[*i + 1] == '$')
	{
		*i += 2;
		return (allocate_gc(o_ft_itoa(data->pid)));
	}
	return (NULL);
}
