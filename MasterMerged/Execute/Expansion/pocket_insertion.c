#include "../execute.h"

static void	init_pocket_struct(t_pocket *pc)
{
	pc->i = 0;
	pc->j = 0;
	pc->keylen = 0;
	pc->value = NULL;
}

static int	get_keylen(char *str, t_data *data)
{
	data->pc.keylen = 0;
	if (str[data->pc.i + 1] >= '0' && str[data->pc.i + 1] <= '9')
		return (data->pc.keylen + 1);
	while (ft_isalnum(str[data->pc.i + 1 + data->pc.keylen])
		|| str[data->pc.i + 1 + data->pc.keylen] == '_')
		data->pc.keylen++;
	return (data->pc.keylen);
}

static bool	is_in_assignment(char *str)
{
	if (ft_strchr(str, '=') && str[0] != '$')
		return (true);
	return (false);
}

static int	env_key(char *str, t_data *data, char ***pockets, bool was_d_quoted)
{
	char	*raw;
	bool	is_assignment;

	is_assignment = is_in_assignment(str);
	data->pc.keylen = get_keylen(str, data);
	if (data->pc.keylen > 0)
	{
		raw = expand_key_wrapper(str, data);
		if (has_space(raw) && !only_spaces(raw)
			&& !was_d_quoted && !is_assignment)
			expand_unqoted_d(pockets, data, raw);
		else
			(*pockets)[data->pc.j++] = raw;
	}
	else
		(*pockets)[data->pc.j++] = standalone(&data->pc.i);
	return (EXIT_SUCCESS);
}

// entry function
int	pocket_insertion(char **pockets, char *str, t_data *data, bool was_d_quoted)
{
	init_pocket_struct(&data->pc);
	while (str[data->pc.i])
	{
		if (str[data->pc.i] == '$')
		{
			if (str[data->pc.i + 1] == '?' || str[data->pc.i + 1] == '$')
				pockets[data->pc.j++] = expand_special_cases(str, data,
						&data->pc.i);
			else
				env_key(str, data, &pockets, was_d_quoted);
		}
		else
			pockets[data->pc.j++] = normal_text(str, &data->pc.i);
	}
	return (data->pockets = pockets, EXIT_SUCCESS);
}
