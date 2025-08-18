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

static int	append_ifs(t_ifs_vars *ifs, char *str)
{
	ifs->ifs_split = ft_split(str, (char)1);
	ifs->j = 0;
	while (ifs->ifs_split[ifs->j])
	{
		if (add_ifs_back(&ifs->ifs_list,
				ifs->ifs_split[ifs->j++]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**ifs_pass(char **argv)
{
	t_ifs_vars	ifs;

	ifs.i = 0;
	ifs.ifs_list = NULL;
	while (argv[ifs.i])
	{
		if (has_delim(argv[ifs.i]))
		{
			if (append_ifs(&ifs, argv[ifs.i]) != EXIT_SUCCESS)
				return (NULL);
		}
		else
		{
			if (add_ifs_back(&ifs.ifs_list, argv[ifs.i]) != EXIT_SUCCESS)
				return (NULL);
		}
		ifs.i++;
	}
	ifs.new_argv = ifs_list_to_argv(ifs.ifs_list);
	if (!ifs.new_argv)
		return (NULL);
	return (ifs.new_argv);
}

char	*red_ifs_pass(char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	cleaned = allocate_gc(malloc(sizeof(char) * (o_ft_strlen(str) + 1)));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != (char)1 && str[i] != (char)127)
		{
			cleaned[j] = str[i];
			j++;
		}
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
