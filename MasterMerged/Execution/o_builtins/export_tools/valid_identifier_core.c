/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_identifier_core.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:24:39 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:06 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

static bool	valid_first_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

static bool	valid_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= '0' && c <= '9')
		return (true);
	if (c == '_' || c == '=' || c == '+')
		return (true);
	return (false);
}

bool	valid_identifier_core(char *str, int *i, bool *standalone)
{
	if (!valid_first_char(str[(*i)++]))
		return (false);
	while (str[*i])
	{
		if (!valid_char(str[*i]))
			return (false);
		if (str[*i] == '=' || str[*i] == '+')
		{
			*standalone = false;
			break ;
		}
		(*i)++;
	}
	return (true);
}
