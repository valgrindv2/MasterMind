/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:30:10 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:15 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = (char *) malloc ((gnl_ft_strlen(s1) + gnl_ft_strlen(s2)) + 1);
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

size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_ft_strdup(char *s1)
{
	size_t	i;
	char	*ptr;

	ptr = (char *) malloc(sizeof(char) * (gnl_ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*gnl_ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (start > gnl_ft_strlen(s))
		return (gnl_ft_strdup(""));
	if (len > gnl_ft_strlen(s + start))
		len = gnl_ft_strlen(s + start);
	sub = (char *) malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return ((char *)sub);
}

char	*gnl_ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char) c;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (a == s[i])
			return ((char *)s + i);
		i++;
	}
	if (a == s[i])
		return ((char *)s + i);
	return (0);
}
