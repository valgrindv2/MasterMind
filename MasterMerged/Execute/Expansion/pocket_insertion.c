#include "../execute.h"

static void init_pocket_struct(t_pocket *pc)
{
    pc->i = 0;
    pc->j = 0;
    pc->keylen = 0;
    pc->value = NULL;
}

static int get_keylen(char *str, t_data *data)
{
	data->pc.keylen = 0;
	if (str[data->pc.i + 1] >= '0' && str[data->pc.i + 1] <= '9')
		return (data->pc.keylen + 1);
	while (ft_isalnum(str[data->pc.i + 1 + data->pc.keylen])
		|| str[data->pc.i + 1 + data->pc.keylen] == '_')
		data->pc.keylen++;
	return (data->pc.keylen);
}

static int env_key(char *str, t_data *data, char ***pockets, bool was_d_quoted)
{
    char    *raw;

	data->pc.keylen = get_keylen(str, data);
	if (data->pc.keylen > 0) // valid key
	{
		raw = expand_key_wrapper(str, data);
        if (!raw)
            return ((*pockets)[data->pc.j++] = raw, EXIT_FAILURE); // free backwards.
        if (has_space(raw) && !was_d_quoted) // removed the comparing to export first arg ............................
        {
            if (internal_field_seperator(raw, data, pockets) != EXIT_SUCCESS)
				return (data->pc.j++, EXIT_FAILURE);
        }
        else
		    (*pockets)[data->pc.j++] = raw;
	}
	else // standalone $
	{
		(*pockets)[data->pc.j] = standalone(&data->pc.i);
		if (!(*pockets)[data->pc.j++])
			return(EXIT_FAILURE); // free backwards.
	}
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
			{
				pockets[data->pc.j] = expand_special_cases(str, data, &data->pc.i);
				if (!pockets[data->pc.j++])
					return(fail_procedure(pockets, data), EXIT_FAILURE); // free backwards.
			}
			else 
			{
                if (env_key(str, data, &pockets, was_d_quoted) != EXIT_SUCCESS)
					return (fail_procedure(pockets, data), EXIT_FAILURE);
			}
		}
		else
		{
			pockets[data->pc.j] = normal_text(str, &data->pc.i);
			if (!pockets[data->pc.j++])
				return(fail_procedure(pockets, data), EXIT_FAILURE); // free backwards.
		}
	}
	return (pockets[data->pc.j] = NULL, EXIT_SUCCESS);
}
