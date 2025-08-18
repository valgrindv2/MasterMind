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

bool	still_has_anon(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ANON)
			return (true);
		i++;
	}
	return (false);
}

static bool	has_anons_inside(int from, int till, char **argv)
{
	while (from <= till)
		if (still_has_anon(argv[from++]))
			return (true);
	return (false);
}

bool	anon(t_tree *node, size_t argc)
{
	if (argc == 1 && node->argv[0][0] == ANON && node->argv[0][1] == '\0')
		return (true);
	if (!has_anons_inside(0, argc - 1, node->argv))
		return (false);
	node->argv = terminate_inside_anons(node->argv);
	if (!node->argv)
		return (true);
	return (false);
}
