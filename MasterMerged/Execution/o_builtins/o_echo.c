/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:05:09 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:58 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

int	valide_option(char *str)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '-' && i == 0)
		{
			op = 1;
			i++;
		}
		if (op == 0)
			return (0);
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_args(t_tree *node, bool *newline)
{
	int		i;
	bool	print_all;

	i = 1;
	print_all = false;
	while (node->argv[i])
	{
		while (print_all == false && valide_option(node->argv[i]))
			i++;
		if (!node->argv[i])
			break ;
		write(1, node->argv[i], o_ft_strlen(node->argv[i]));
		print_all = true;
		if (node->argv[i] && node->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (*newline == true)
		write(1, "\n", 1);
}

int	o_echo(t_tree *node)
{
	bool	newline;

	if (!node->argv[1])
		return (printf("\n"), EXIT_SUCCESS);
	newline = true;
	if (valide_option(node->argv[1]))
		newline = false;
	return (echo_args(node, &newline), EXIT_SUCCESS);
}
