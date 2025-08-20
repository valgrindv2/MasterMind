/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoiner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:53 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

size_t	count_strings_len(char **list)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (list[i])
	{
		len += o_ft_strlen(list[i]);
		i++;
	}
	return (len);
}

void	copy_with_sep(char **list, char *sep, size_t size, char *joined)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (list[i])
	{
		j = 0;
		while (list[i][j])
			joined[k++] = list[i][j++];
		if (i < size - 1)
		{
			j = 0;
			while (sep[j])
				joined[k++] = sep[j++];
		}
		i++;
	}
	joined[k] = '\0';
}

char	*strjoiner(char **list, char *sep, size_t size)
{
	size_t	total_len;
	size_t	strings_len;
	char	*joined;

	if (!list || !sep || size == 0)
		return (NULL);
	if (size == 1)
		return (ft_strdup(list[0]));
	strings_len = count_strings_len(list);
	total_len = strings_len + (o_ft_strlen(sep) * (size - 1));
	joined = malloc(total_len + 1);
	if (!joined)
		return (NULL);
	copy_with_sep(list, sep, size, joined);
	return (joined);
}
