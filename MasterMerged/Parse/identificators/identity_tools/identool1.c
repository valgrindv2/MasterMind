/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identool1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:13:45 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/18 07:37:24 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_of_string(char *input, int index)
{
	int	len;

	len = 0;
	while (input[index])
	{
		if (check_alpha(input[index], input[index + 1]))
			break ;
		len++;
		index++;
	}
	return (len);
}

char	*scrap_string(char *input, int *index)
{
	int		i;
	char	*scrap;

	i = 0;
	scrap = malloc(len_of_string(input, *index) + 1);
	if (!scrap)
		return (NULL);
	while (input[*index])
	{
		if (check_alpha(input[*index], input[*index + 1]))
			break ;
		scrap[i] = input[*index];
		(*index)++;
		i++;
	}
	scrap[i] = '\0';
	return (scrap);
}

char	*scrap(int *index, char *scrapped)
{
	int		len;
	char	*token;

	len = get_len(scrapped);
	token = ft_strdup(scrapped);
	while (len--)
		(*index)++;
	return (token);
}

int	len_of_quote(char *input, char quote_case, int index)
{
	int	len;

	len = 0;
	while (input[index])
	{
		len++;
		index++;
		if (input[index] == quote_case)
		{
			len++;
			break ;
		}
	}
	return (len);
}

char	*scrap_quote(char *input, t_data *dt, int quote_case)
{
	int		i;
	char	*quote;

	i = 0;
	if (!realt_quotes(input, quote_case, dt->i, QUOTES_ERR))
		return (dt->exit_status = 2, NULL);
	quote = malloc(len_of_quote(input, quote_case, dt->i) + 1);
	if (!quote)
		return (NULL);
	while (input[dt->i])
	{
		quote[i] = input[dt->i];
		i++;
		dt->i++;
		if (input[dt->i] == quote_case)
		{
			quote[i] = input[dt->i];
			dt->i++;
			i++;
			break ;
		}
	}
	quote[i] = '\0';
	return (quote);
}
