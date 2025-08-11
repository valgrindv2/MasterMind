#include "../minishell.h"
# define BUFFER 10000000

static void	read_data(t_red *curr)
{
	int i = 0;
	char string[BUFFER];
	ssize_t bytes = read(curr->fd_here_doc, &string, BUFFER);
	while (bytes != -1 && bytes != 0)
		bytes = read(curr->fd_here_doc, &string, BUFFER);
	printf("Current Heredoc [%s]\n", curr->value);
	while (string[i])
	{
		write(1, &string[i], 1);
		i++;
	}
}

void	read_files(t_token *curr)
{
	while (curr)
	{
		if (curr->red != NULL)
		{
			if (curr->red->tok == DEL_ID)
				read_data(curr->red);
		}
		curr = curr->next;
	}
}