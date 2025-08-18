/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arglist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 16:02:06 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

bool	has_delim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)1)
			return (true);
		i++;
	}
	return (false);
}

bool	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (true);
		i++;
	}
	return (false);
}
