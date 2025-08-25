/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:35:19 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:17 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

bool	has_ambig_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t'
			|| str[i] == (char)1 || str[i] == (char)127)
			return (true);
		i++;
	}
	return (false);
}

bool	expandable_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	has_ifs(char *str)
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

char	*expand_heredoc(char *joined, t_red *red, t_data *data)
{
	char	*expanded;

	if (!red->was_d_quote && !red->was_s_quote)
		expanded = expand_double_quoted(joined, data);
	else
		expanded = joined;
	return (expanded);
}

bool	check_expanded_malloc(char **expanded, t_data *data, t_red *curr_red)
{
	if (curr_red->was_s_quote)
		*expanded = allocate_gc(ft_strdup(curr_red->value));
	else if (curr_red->was_d_quote)
		*expanded = expand_double_quoted(curr_red->value, data);
	else
		*expanded = expand_double_quoted(curr_red->value, data);
	if (!*expanded)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
