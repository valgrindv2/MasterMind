/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:22 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	*o_ft_strtrim(char *s, char *set)
{
	int	start;
	int	end;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	end = o_ft_strlen(s);
	if (end == 0)
		return (allocate_gc(ft_substr(s, 0, 0)));
	end--;
	while (end > start && ft_strchr(set, s[end]))
		end--;
	return (allocate_gc(ft_substr(s, start, end - start + 1)));
}

static char	*trim_key_spaces(char *key)
{
	char	*trimmed;

	if (!key)
		return (NULL);
	trimmed = o_ft_strtrim(key, " \t\n\v\f\r");
	return (trimmed);
}

char	*find_in_env(t_envlist *envlist, char *key)
{
	t_envlist	*cur;
	char		anon[2];

	cur = envlist;
	key = trim_key_spaces(key);
	anon[0] = ANON;
	anon[1] = '\0';
	while (cur)
	{
		if (ft_strcmp(key, cur->variable) == 0)
		{
			if (cur->value[0] == '\0')
				return (allocate_gc(ft_strdup(anon)));
			return (allocate_gc(ft_strdup(cur->value)));
		}
		cur = cur->next;
	}
	return (allocate_gc(ft_strdup(anon)));
}

char	*expand_key(char *str, t_data *data, int keylen, int *i)
{
	char	*value;
	char	*key;

	key = allocate_gc(ft_substr(str, *i + 1, keylen));
	*i += keylen + 1;
	value = find_in_env(data->env, key);
	return (value);
}
