/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pocket_expantion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:52 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// char	*normal_text(char *str, int *i)
// {
// 	int	start;

// 	start = *i;
// 	while (str[*i] && str[*i] != '$')
// 		(*i)++;
// 	return (allocate_gc(ft_substr(str, start, *i - start)));
// }

// char	*standalone(int *i)
// {
// 	(*i)++;
// 	return (allocate_gc(ft_strdup("$")));
// }

// char	*expand_key_wrapper(char *str, t_data *data)
// {
// 	data->pc.value = expand_key(str, data, data->pc.keylen, &data->pc.i);
// 	if (data->pc.value != NULL)
// 		return (data->pc.value);
// 	else if (data->pc.value == NULL)
// 		return (NULL);
// 	return (perror("WHY!"), NULL);
// }
