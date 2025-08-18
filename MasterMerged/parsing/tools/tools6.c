/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:29:27 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/18 09:15:23 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if ((char)c == '\0')
		return (1);
	return (0);
}

char	*copy_var(char *value_case)
{
	int		i;
	int		y;
	char	*value_base;

	i = 1;
	y = 0;
	value_base = malloc((get_len(value_case) - 1) + 1);
	if (!value_base)
		return (NULL);
	while (value_case[i])
	{
		value_base[y] = value_case[i];
		y++;
		i++;
	}
	value_base[y] = '\0';
	return (value_base);
}

void	puterror(char *str)
{
	if (!str)
		return ;
	write(2, str, o_ft_strlen(str));
}

void	print_error(char *error, char *err, int mode)
{
	puterror(error);
	if (mode == SYN)
	{
		write(2, "`", 1);
		puterror(err);
		write(2, "\'", 1);
		write(2, "\n", 2);
	}
	if (mode == NL)
		write(2, "\n", 2);
}
