/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:29:38 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/03 20:32:51 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**free_str(char **str, int i)
{
	while (i >= 0)
	{
		free (str[i]);
		i--;
	}
	free (str);
	return (NULL);
}

static size_t	words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*pusher(char const *s, char *split, size_t wl, size_t i)
{
	size_t	j;

	j = 0;
	while (wl > 0)
	{
		split[j] = s[i - wl];
		j++;
		wl--;
	}
	split[j] = '\0';
	return (split);
}

static char	**extractor(char const *s, char c, char **split, size_t toklen)
{
	size_t	i;
	size_t	w;
	size_t	wl;

	i = 0;
	w = 0;
	while (w < toklen)
	{
		while (s[i] && s[i] == c)
			i++;
		wl = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			wl++;
		}
		split[w] = allocate_gc(malloc(wl + 1));
		if (!split[w])
			return (free_str(split, w));
		pusher(s, split[w], wl, i);
		w++;
	}
	split[w] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	tokens;

	if (!s)
		return (NULL);
	tokens = words(s, c);
	new = allocate_gc(malloc((tokens + 1) * (sizeof(char *))));
	if (!new)
		return (NULL);
	new = extractor(s, c, new, tokens);
	return (new);
}
