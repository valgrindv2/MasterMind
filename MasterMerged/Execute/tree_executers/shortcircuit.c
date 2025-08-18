/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcircuit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:53:05 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 15:53:05 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	short_circuit_operand(t_tree *node, t_grammar operand_id, t_data *data)
{
	int	left_status;

	left_status = recursive_execution(node->left, data);
	if (operand_id == AND_ID)
	{
		if (left_status == EXIT_SUCCESS)
			return (recursive_execution(node->right, data));
		else
			return (left_status);
	}
	else if (operand_id == OR_ID)
	{
		if (left_status != EXIT_SUCCESS)
			return (recursive_execution(node->right, data));
		else
			return (left_status);
	}
	return (EXIT_FAILURE);
}
