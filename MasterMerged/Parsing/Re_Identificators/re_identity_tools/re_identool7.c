#include "../../minishell.h"

static int	insert_fake_cmd(t_token *id_class, t_token *before, int mode)
{
	t_token	*in;
	t_token	*tmp;

	in = add_identity(ft_strdup(FAKE), COMMAND_ID, D_INIT, NULL);
	if (!in)
			return (0);
	init_properties(in);
	in->fake = true;
	if (mode == INSIDE)
	{
		tmp = before->next;
		before->next = in;
		in->next = tmp;
	}
	else if (mode == LAST)
	{
		id_class->next = in;
		in->next = NULL;
	}
	return (1);
}

int	fake_system(t_token *id_class)
{
	t_token	*before;
	bool	cmd_found;

	cmd_found = false;
	while (id_class != NULL)
	{
		if (id_class->tok == COMMAND_ID)
			cmd_found = true;
		if (id_class->op_case && cmd_found == false)
		{
			if (!insert_fake_cmd(id_class, before, INSIDE))
				return (0);
		}
		if (!id_class->next && cmd_found == false)
		{
				if (!insert_fake_cmd(id_class, before, LAST))
					return (0);
		}
		else if (id_class->op_case && cmd_found == true)
			cmd_found = false;
		before = id_class;
		id_class = id_class->next;
	}
	return (1);
}
/*
		> f1 > f3 || << ok cat | >f2
		 >f1 > f2 || >f3 << ok && >> f4
*/