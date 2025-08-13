#include "../minishell.h"

# define BUFFER 100000


void	read_fd(int fd, char *curr)
{
	char c;
	char *buffer = malloc(10000000);
	printf("fd enterd > %d\n", fd);
	printf("DATA FOR HEREDOC [%s] > \n", curr);
	lseek(fd, 0, SEEK_SET);
	ssize_t bytes = read(fd, &c, 1);
	if (bytes == -1)
	{
		perror("READ FAILED");
		exit(F);
	}
	int x = 0;
	while (bytes > 0)
	{
		buffer[x++] = c;
		bytes = read(fd, &c, 1);
		if (bytes == -1)
		{
				perror("READ FAILED");
				exit(F);
		}
	}
	buffer[x] = '\0';
	x = 0;
	while (buffer[x])
	{
		write(1, &buffer[x], 1);
		x++;
	}
}

void	read_files(t_token *curr, int fd, char *list)
{
	(void)fd;

	printf("%s\n", list);
	while (curr)
	{
		while (curr->red != NULL)
		{
			if (curr->red->tok == DEL_ID)
				read_fd(curr->red->fd_here_doc, curr->red->value);
			curr->red = curr->red->next;
		}
		curr = curr->next;
	}
	// while (curr)
	// {
	// 	if (curr->tok == DEL_ID)
	// 		read_fd(curr->here_doc_fd, curr->identity);
	// 	curr = curr->next;
	// }
}

/*
	(CHECKED) Storing from data struct heredocs is fine, all nodes of Heredoc
	got their fds properly
	(CHECKED) Sroting from the first list (id_class into re_built), is good
	
	
	Why fail in storing into redirections struct ??
*/