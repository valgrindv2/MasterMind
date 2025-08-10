#include "../../minishell.h"

char	*scrap_braces(char *input, int *index, char *brace)
{
	int	len;

	len = get_len(brace);
	while (len--)
		(*index)++;
	return (ft_strdup(brace));
}

int	realt_quotes(char *input, int doubles_case, int index, char *err)
{
	int	doubles;

	doubles = 0;
	if (!ft_strchr(input, doubles_case))
		return (1);
	while (input[index])
	{
		if (input[index] == doubles_case
			&& doubles == 1)
		{
			doubles++;
			break ;
		}
		if (input[index] == doubles_case)
			doubles++;
		index++;
	}
	if (doubles % 2 != 0)
	{
		print_error(err, NULL, 0);
		return (0);
	}
	return (1);
}

int	printer(t_token *curr, char *name)
{
	while (curr)
	{
		printf("\e[0;36;1m%s > %s\n\e[0m", name , curr->identity);
		// if (curr->red) 
		//     printer_red(curr->red, "Redirections ");
		curr = curr->next;
	}
	return (1);
}

void	print_tok(t_red *curr)
{
	if (curr->tok == 0)
			printf("ID-> PIPE\n");
		else if (curr->tok == 1)
			printf("ID-> RED_IN_ID\n");
		else if (curr->tok == 2)
			printf("ID-> RED_OUT_ID\n");
		else if (curr->tok == 3)
			printf("ID-> RED_APP_ID\n");
		else if (curr->tok == 4)
		   printf("ID-> HERE_DOC_ID\n");
		else if (curr->tok == 5)
			printf("ID-> AND_ID\n");
		else if (curr->tok == 6)
			printf("ID-> OR_ID\n");
		else if (curr->tok == 7)
			printf("ID-> BRACE_O_ID\n");
		else if (curr->tok == 8)
			printf("ID-> BRACE_C_ID\n");
		else if (curr->tok == 9)
			printf("ID-> S_QUOTE_ID\n");
		else if (curr->tok == 10)
			printf("ID-> D_QUOTE_ID\n");
		else if (curr->tok == 11)
			printf("ID-> STRING_ID\n");
		else if (curr->tok == 12)
		{
			printf("ID-> DEL_ID\n");
			if (curr->was_d_quote)
			{
				printf("      └─ ");
				printf(" [ Delimiter was D_Quoted ]\n");
			}
			else if (curr->was_s_quote)
			{
				printf("      └─ ");
				printf("[ Delimiter was S_Quoted ]\n");
			}

			if (curr->fd_here_doc != -1)
			{
				printf("      └─ ");
				printf("File Descriptor Ready [fd %d]\n", curr->fd_here_doc);
			}
			else if (curr->fd_here_doc == -1)
			{
				printf("      └─ ");
				printf("heredoc [fd %d]\n", curr->fd_here_doc);
			}
		}
		else if (curr->tok == 13)
			printf("ID-> INPUT_FILE_ID\n");
		else if (curr->tok == 14)
			printf("ID-> OUTPUT_FILE_ID\n");
		else if (curr->tok == 15)
			printf("ID-> INPUT_APP_FILE_ID\n");
		else if (curr->tok == 16)
			printf("ID-> COMMAND_ID\n");
		else if (curr->tok == 17)
			printf("ID-> ARG_ID\n");
}

int	printer_red(t_red *curr, char *name)
{
	while (curr != NULL)
	{
		printf("      └─ ");
		printf("\e[0;36;1m%s > %s --> \e[0m", name , curr->value);
		print_tok(curr);
		curr = curr->next;
	}
	return (1);
}

int	printer_arg(t_arg *curr, char *name)
{
	while (curr != NULL)
	{
		printf("      └─ ");
		printf("\e[0;36;1m%s > %s --> \e[0m", name , curr->value);
		// print_tok(curr);
		printf("Quoted > %d\n", curr->was_s_quote);
		if (curr->space_next == true)
		{
			printf("      └─ ");
			printf("Space Next True\n");
		}
		curr = curr->next;
	}
	return (1);
}