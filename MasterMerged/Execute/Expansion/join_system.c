/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 05:17:55 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

char	*o_ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || (s1[0] == ANON && s1[1] == '\0'))
		return (ft_strdup(s2));
	if (!s2 || (s2[0] == ANON && s2[1] == '\0'))
		return (ft_strdup(s1));
	ptr = (char *) malloc ((o_ft_strlen(s1) + o_ft_strlen(s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return ((ptr));
}

static char	*merge_pockets(char **lst)
{
	char	*joined;
	size_t	i;

	i = 0;
	joined = NULL;
	while (lst[i])
	{
		joined = allocate_gc(o_ft_strjoin(joined, lst[i]));
		i++;
	}
	return (joined);
}

// join double array char **
char	*pocket_joiner(char **pockets)
{
	char	*res;

	res = merge_pockets(pockets);
	return (res);
}

char	*join_system(t_arg **p_arg)
{
	t_arg	*curr;
	char	*res;

	res = NULL;
	curr = *p_arg;
	while (curr)
	{
		res = allocate_gc(o_ft_strjoin(res, curr->value));
		if (curr->space_next || ft_strchr(curr->value, ANON))
		{
			curr = curr->next;
			break ;
		}
		curr = curr->next;
	}
	*p_arg = curr;
	return (res);
}
