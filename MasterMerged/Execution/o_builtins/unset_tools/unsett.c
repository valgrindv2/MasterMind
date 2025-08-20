/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsett.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:41:56 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:07 by ayel-bou         ###   ########.fr       */
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
	if (c == '_')
		return (true);
	return (false);
}

bool	valid_identifier_un(char *str)
{
	int		i;
	bool	standalone;

	i = 0;
	standalone = true;
	if (!valid_first_char(str[i++]))
		return (false);
	while (str[i])
	{
		if (!valid_char(str[i]))
			return (false);
		else
		{
			if (str[i] == '=' || str[i] == '+')
			{
				standalone = false;
				break ;
			}
		}
		i++;
	}
	if (standalone)
		return (true);
	return (check_identifier(str, i));
}

void	delete(t_envlist *node)
{
	free(node->value);
	free(node->variable);
	free(node);
}
