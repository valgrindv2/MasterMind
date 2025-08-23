/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:38:12 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/23 05:24:38 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	scan_for_doubles(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr != NULL)
	{
		if (curr->tok == BRACE_O_ID
			|| curr->tok == BRACE_C_ID)
			return (1);
		curr = curr->next;
	}
	return (0);
}

static int	non_print(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if ((0 <= in[i] && in[i] <= 32) || in[i] == 127)
			return (0);
		i++;
	}
	return (1);
}

static void	in_alert(t_token *token, int *flag_in)
{
	while (token != NULL)
	{
		if (token->tok == BRACE_C_ID)
			break ;
		if ((0 <= token->tok && token->tok <= 6)
			|| (9 <= token->tok && token->tok <= 12))
			*flag_in = 1;
		token = token->next;
	}
}

static int	closing_evaluation(t_token *token, t_data *data)
{
	t_token	*point;
	t_token	*braces;
	t_token	*stack_br;

	(void)data;
	if (!token)
		return (1);
	stack_br = NULL;
	braces = get_all_braces(token);
	point = braces;
	if (!braces)
		return (ANOMALY);
	while (braces != NULL)
	{
		if (!push_br(&stack_br, braces))
			return (clean_stacks(&stack_br, &point), 0);
		braces = braces->next;
	}
	if (stack_br != NULL)
	{
		clean_stacks(&stack_br, &point);
		return (0);
	}
	list_cleaner(&point);
	return (1);
}

int	doubles_verify(t_token *token, t_data *data)
{
	int		flag_in;
	t_token	*curr;

	flag_in = 0;
	curr = token;
	while (curr != NULL && curr->next != NULL)
	{
		if (curr->tok == BRACE_O_ID)
		{
			in_alert(curr->next, &flag_in);
			if ((!non_print(curr->next->identity) && !flag_in)
				|| (curr->tok == BRACE_O_ID && curr->next->tok == BRACE_C_ID))
			{
				syntax_error_found(curr->next, data);
				return (0);
			}
		}
		curr = curr->next;
	}
	data->br_fail = closing_evaluation(token, data);
	if (data->br_fail == ANOMALY)
		return (0);
	if (data->br_fail == 0 && data->no_sef == true)
		return (print_error(BRACE_ERR, NULL, 0), 0);
	return (1);
}
