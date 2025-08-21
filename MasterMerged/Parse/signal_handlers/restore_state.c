/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:01:22 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/16 07:26:48 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_current_state(int fd, t_data *data)
{
	struct termios	current_state;

	if (tcgetattr(fd, &current_state) == -1)
		return (0);
	data->saved_state = current_state;
	return (1);
}

int	restore_previous_state(int fd, t_data *data)
{
	if (tcsetattr(fd, TCSANOW, &data->saved_state) == -1)
		return (0);
	return (1);
}
