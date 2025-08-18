#include "../execute.h"

static void	print_errno(char *str)
{
	int	i;

	i = 0;
	puterror("Master@Mind: ");
	write(2, str, o_ft_strlen(str));
	write(2, "\n", 1);
}

int	errors_msgs(int err)
{
	if (err == 127)
		return (puterror("Master@Mind: command not found\n"), 127);
	if (!ft_strcmp("No such file or directory", strerror(err))
		|| !ft_strcmp("command not found", strerror(err)))
		return (print_errno(strerror(err)), 127);
	else if (!ft_strcmp("Permission denied", strerror(err))
		|| !ft_strcmp("is a directory", strerror(err))
		|| !ft_strcmp("Not a directory", strerror(err)))
		return (print_errno(strerror(err)), 126);
	else if (err == 22 || err == 21)
		return (puterror("Master@Mind: is a directory\n"), 126);
	return (err);
}

int	is_it_dir(char *cmd)
{
	struct stat dir;

	if (stat(cmd, &dir) < 0)
		return (mind_free_all(PANIC), 0);
	return (S_ISDIR(dir.st_mode));
}
