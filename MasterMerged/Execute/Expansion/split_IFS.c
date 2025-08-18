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
	int		i;
	int		j;
	char	**new_pocket;
	int		mc_argc;
	char	**split;

	split = tab_split(raw, " \t\n\v\f\r");
	mc_argc = arg_count(split);
	new_pocket = allocate_gc(malloc((data->pc.j + mc_argc + 1)
				* sizeof(char *)));
	i = 0;
	while (i < data->pc.j)
	{
		new_pocket[i] = allocate_gc(ft_strdup((*pockets)[i]));
		i++;
	}
	j = 0;
	while (split[j])
	{
		if (j == 0)
			new_pocket[i++] = back_append_delimiter(split[j++]);
		else if (split[j] && split[j + 1] == NULL)
			new_pocket[i++] = front_append_delimiter(split[j++]);
		else
			new_pocket[i++] = append_delimiter(split[j++]);
	}
	return (new_pocket[i] = NULL, (*pockets) = new_pocket,
		data->pc.j = i, EXIT_SUCCESS);
}
