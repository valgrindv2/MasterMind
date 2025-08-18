/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export_arg_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:19:20 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 14:19:20 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execute.h"

int	process_new_var(char *arg, t_data *data)
{
	if (has_equal(arg))
	{
		if (has_plus(arg))
		{
			if (append_value(arg, data->env) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else if (add_to_envlist(&data->env, arg, EXPORTED) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_to_envlist(&data->env, arg, NO_VALUE) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_existing_var(char *arg, t_data *data)
{
	if (has_plus(arg))
	{
		if (append_value(arg, data->env) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (has_equal(arg))
	{
		if (assign_new_value(arg, data->env) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
