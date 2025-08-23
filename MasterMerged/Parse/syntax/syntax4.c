/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 07:24:56 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/23 16:04:09 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	op_braces(int *qu, char *np, char x)
{
	if (*qu && *np == x)
	{
		*qu = 0;
		*np = ANON;
	}
	else if (!*qu && (x == '\'' || x == '"'))
	{
		*qu = 1;
		*np = x;
	}
}

int	evaluate_case(char *input, t_data *data)
{
	int		i;
	int		op;
	int		cl;
	int		qu;
	char	np;

	i = 0;
	op = 0;
	cl = 0;
	qu = 0;
	np = ANON;
	while (input[i])
	{
		op_braces(&qu, &np, input[i]);
		if (!qu && input[i] == '(')
			op++;
		else if (!qu && input[i] == ')')
			cl++;
		if (cl > op)
			return (0);
		i++;
	}
	if (cl == op)
		data->no_sef = false;
	return (cl == op);
}
