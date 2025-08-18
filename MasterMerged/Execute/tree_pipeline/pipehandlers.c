/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipehandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:07:50 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 16:07:50 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	pipe_sighandle(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	start_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
