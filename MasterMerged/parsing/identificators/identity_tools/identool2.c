/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 07:53:44 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:53:45 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*scrap_braces(char *input, int *index, char *brace)
{
	int	len;

	(void)input;
	len = get_len(brace);
	while (len--)
		(*index)++;
	return (ft_strdup(brace));
}

int	realt_quotes(char *input, int doubles_case, int index, char *err)
{
	int	doubles;

	doubles = 0;
	if (!ft_strchr(input, doubles_case))
		return (1);
	while (input[index])
	{
		if (input[index] == doubles_case
			&& doubles == 1)
		{
			doubles++;
			break ;
		}
		if (input[index] == doubles_case)
			doubles++;
		index++;
	}
	if (doubles % 2 != 0)
	{
		print_error(err, NULL, 0);
		return (0);
	}
	return (1);
}
