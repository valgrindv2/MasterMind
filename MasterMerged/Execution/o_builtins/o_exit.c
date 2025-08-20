/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:11:48 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:00 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static int	ifnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		i++;
		if (i > 2)
			return (0);
	}
	if (i == 1)
		return (11);
	return (1);
}

static long	warn_exit(const char *str)
{
	size_t		i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (EXIT_OVER_LIMIT);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (EXIT_OVER_LIMIT);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (MAX_FLOW);
}

static void	numeric_value(char *str, t_data *data)
{
	if (!ifnumber(str) || warn_exit(str) == EXIT_OVER_LIMIT)
	{
		if (data->child_state == false)
			puterror("exit\n");
		puterror("Master@Mind: Exit Requires A Numeric Value\n");
		data->exit_status = 255;
		mind_free_all(PANIC);
	}
}

int	o_exit(t_tree *node, t_data *data)
{
	char	**argv;
	long	exit_call;

	argv = node->argv;
	if (count_args(argv) == 11)
	{
		if (data->child_state == false)
			puterror("exit\n");
		mind_free_all(PANIC);
	}
	numeric_value(argv[1], data);
	if (!count_args(argv))
	{
		if (data->child_state == false)
			puterror("exit\n");
		puterror("exit: too many arguments\n");
		return (1);
	}
	if (data->child_state == false)
		puterror("exit\n");
	exit_call = ft_atol(argv[1]);
	data->exit_status = exit_call;
	mind_free_all(PANIC);
	return (EXIT_SUCCESS);
}
