/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsett2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:51:01 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:09 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Parse/minishell.h"

static bool	is_printable(char c)
{
	if (c == '=')
		return (true);
	if ((c >= 32 && c <= 126) || c == '\0')
	{
		return (true);
	}
	return (false);
}

int	valide_unset(char *str, int i)
{
	if (str[i] == '+' && str[i + 1] != '=')
		return (false);
	if (str[i] == '=' && !is_printable(str[i + 1]))
		return (false);
	return (true);
}

int	init_mini(int *i, bool *stand)
{
	*i = 0;
	*stand = true;
	return (0);
}

bool	check_identifier(char *str, int i)
{
	if (str[i] == '+' && str[i + 1] != '=')
		return (false);
	if (str[i] == '=' && !is_printable(str[i + 1]))
		return (false);
	return (true);
}
