#include "../minishell.h"

static int check_braces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ')' || input[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

static int count_braces(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == ')' || input[i] == '(')
			count++;
		i++;
	}
	return (count);
}

static char	*all_braces(char *input)
{
	int		i;
	int		y;
	char 	*br;

	i = 0;
	y = 0;
	br = malloc(count_braces(input) + 1);
	if (!br)
		return (NULL);
	while (input[i])
	{
		if (input[i] == ')' || input[i] == '(')
		{
			br[y] = input[i];
			y++;
		}
		i++;
	}
	br[y] = '\0';
	return (br);
}

int	edge_braces(char *input, t_data *data)
{
	char	*braces;

	data->no_sef = false;
	if (!check_braces(input))
		return (0);
	braces = all_braces(input);
	if (!braces || !operations_braces(braces, data))
	{
		free(braces);
		return (0);
	}
	free (braces);
	return (1);
}
