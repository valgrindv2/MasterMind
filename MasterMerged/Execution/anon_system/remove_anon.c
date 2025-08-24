/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_anon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:12 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static int	is_nonprintable_char(char c)
{
	return (c == (char)1 || c == (char)127);
}

static size_t	count_printable_chars(const char *s)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!is_nonprintable_char(s[i]))
			count++;
		i++;
	}
	return (count);
}

static void	copy_without_nonprintables(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!is_nonprintable_char(src[i]))
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
}

char	**remove_nonprintables_argv(char **argv)
{
	char	**newargv;
	size_t	argc;
	size_t	i;
	size_t	printable_chars;
	char	*clean;

	if (!argv)
		return (free_argv(argv), NULL);
	argc = arg_count(argv);
	newargv = allocate_gc(malloc((argc + 1) * sizeof(char *)));
	i = 0;
	while (i < argc)
	{
		printable_chars = count_printable_chars(argv[i]);
		clean = allocate_gc(malloc(printable_chars + 1));
		copy_without_nonprintables(clean, argv[i]);
		newargv[i] = clean;
		i++;
	}
	newargv[argc] = NULL;
	return (newargv);
}
