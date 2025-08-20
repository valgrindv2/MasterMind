/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:53 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	*append_delimiter(char *str)
{
	char	*first_border;
	char	*last_border;
	char	delim[2];

	delim[0] = (char)1;
	delim[1] = '\0';
	first_border = allocate_gc(gnl_ft_strjoin(delim, str));
	last_border = allocate_gc(gnl_ft_strjoin(first_border, delim));
	return (last_border);
}

char	*front_append_delimiter(char *str)
{
	char	*first_border;
	char	delim[2];

	delim[0] = (char)1;
	delim[1] = '\0';
	first_border = allocate_gc(gnl_ft_strjoin(delim, str));
	return (first_border);
}

char	*back_append_delimiter(char *str)
{
	char	*last_border;
	char	delim[2];

	delim[0] = (char)1;
	delim[1] = '\0';
	last_border = allocate_gc(gnl_ft_strjoin(str, delim));
	return (last_border);
}

bool	only_spaces(char *raw)
{
	int	i;

	i = 0;
	while (raw[i])
	{
		if (raw[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	expand_unqoted_d(char ***pockets, t_data *data, char *raw)
{
	t_udouble	ud;

	ud.split = tab_split(raw, " \t\n\v\f\r");
	ud.mc_argc = arg_count(ud.split);
	ud.new_pocket = allocate_gc(malloc((data->pc.j + ud.mc_argc + 1)
				* sizeof(char *)));
	ud.i = 0;
	while (ud.i < data->pc.j)
	{
		ud.new_pocket[ud.i] = allocate_gc(ft_strdup((*pockets)[ud.i]));
		ud.i++;
	}
	ud.j = 0;
	while (ud.split[ud.j])
	{
		if (ud.j == 0)
			ud.new_pocket[ud.i++] = back_append_delimiter(ud.split[ud.j++]);
		else if (ud.split[ud.j] && ud.split[ud.j + 1] == NULL)
			ud.new_pocket[ud.i++] = front_append_delimiter(ud.split[ud.j++]);
		else
			ud.new_pocket[ud.i++] = append_delimiter(ud.split[ud.j++]);
	}
	return (ud.new_pocket[ud.i] = NULL, (*pockets) = ud.new_pocket,
		data->pc.j = ud.i, EXIT_SUCCESS);
}
