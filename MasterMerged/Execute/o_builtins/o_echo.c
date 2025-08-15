#include "../execute.h"

int valide_option(char *str)
{
	int i;
	int op;

	i = 0;
	op = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '-' && i == 0)
		{
			op = 1;
			i++;
		}
		if (op == 0)
			return (0);
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    echo_args(t_tree *node, bool *newline)
{
	int		i;
	bool	print_all;

	i = 1;
	print_all = false;
	while (node->argv[i])
	{
		if (valide_option(node->argv[i]) && print_all == false)
			i++;
		if (!node->argv[i])
			break ;
		printf("%s", node->argv[i]);
		print_all = true;
		if (node->argv[i + 1])
			printf(" ");
		i++;
	}
	if (*newline == true)
		printf("\n");
}

// function entry
int o_echo(t_tree *node)
{
	bool    newline;

	if (!node->argv[1])
		return (printf("\n"), EXIT_SUCCESS);
	newline = true;
	if (valide_option(node->argv[1]))
		newline = false;
	return (echo_args(node, &newline), EXIT_SUCCESS);
}
// echo -n test -n dsdds -n -nnn$s