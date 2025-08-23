/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:51:14 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/23 16:00:39 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_alpha(char x, char x2)
{
	if (x == PIPE
		|| x == '<'
		|| x == '>'
		|| (x == '&' && x2 == '&')
		|| x == S_QUOTE
		|| x == SPACE
		|| x == D_QUOTE
		|| x == BRACE_CL
		|| x == BRACE_OP
		|| x == TAB
		|| !whitespaces(x))
		return (T);
	return (N);
}

void	cpy_identity(char *dst, char *src)
{
	size_t	i;

	dst = malloc(get_len(src) + 1);
	if (!dst)
		exit(F);
	i = 0;
	while (src[i] && dst != src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (haystack == NULL && len == 0)
		return (S);
	if (needle[0] == 0)
		return (S);
	j = 0;
	i = 0;
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return (F);
		}
		i++;
		j = 0;
	}
	return (S);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
