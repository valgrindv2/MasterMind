/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:27:38 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:07 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

static bool	is_printable(char c)
{
	if (c == '=')
		return (true);
	if ((c >= 32 && c <= 126) || c == '\0'
		|| (((9 <= c && c <= 13) || c == 32)))
	{
		return (true);
	}
	return (false);
}

static bool	check_after_break(char *str, int i)
{
	if (str[i] == '+' && str[i + 1] != '=')
		return (false);
	if (str[i] == '=' && !is_printable(str[i + 1]))
		return (false);
	return (true);
}

bool	valid_identifier(char *str)
{
	int		i;
	bool	standalone;

	i = 0;
	standalone = true;
	if (!str[i])
		return (false);
	if (!valid_identifier_core(str, &i, &standalone))
		return (false);
	if (standalone)
		return (true);
	return (check_after_break(str, i));
}
