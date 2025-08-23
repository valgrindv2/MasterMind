/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_io_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/22 23:37:13 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

t_data	**get_data(void)
{
	static t_data	*data = NULL;

	return (&data);
}

void	set_data(t_data	*dt)
{
	t_data	**data;

	data = get_data();
	*data = dt;
}

void	close_io(void)
{
	t_data	*data;

	data = *get_data();
	if (data->saved_in != -1)
	{
		close(data->saved_in);
		data->saved_in = -1;
	}
	if (data->saved_out != -1)
	{
		close(data->saved_out);
		data->saved_out = -1;
	}
}
