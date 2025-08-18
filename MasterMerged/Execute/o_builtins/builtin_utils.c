/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:51:57 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 14:51:57 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

size_t	arg_count(char **argv)
{
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}
