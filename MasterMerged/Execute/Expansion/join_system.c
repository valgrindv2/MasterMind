#include "../execute.h"

char	*o_ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || (s1[0] == ANON && s1[1] == '\0'))
		return (ft_strdup(s2));
	if (!s2 || (s2[0] == ANON && s2[1] == '\0'))
		return (ft_strdup(s1));
	ptr = (char *) malloc ((o_ft_strlen(s1) + o_ft_strlen(s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return ((ptr));
}

static char	*merge_pockets(char **lst)
{
	char	*joined;
	size_t	i;

	i = 0;
	joined = NULL;
	while (lst[i])
	{
		joined = allocate_gc(o_ft_strjoin(joined, lst[i]));
		i++;
	}
	return (joined);
}

// join double array char **
char	*pocket_joiner(char **pockets)
{
	char	*res;

	res = merge_pockets(pockets);
	return (res);
}

// joins successive t_arg->value pieces until space_next==true
char *join_system(t_arg **p_arg)
{
    t_arg *curr;
    char  *res;
    char  *tmp;

    res = NULL;

    curr = *p_arg;
    while (curr)
    {
        res = allocate_gc(o_ft_strjoin(res, curr->value));
        if (curr->space_next || ft_strchr(curr->value, ANON))  // if the parser marked a space after this piece, consume it and stop
        {
            curr = curr->next;
            break;
        }
        curr = curr->next; // otherwise, keep joining the next piece
    }
    *p_arg = curr;  // advance the caller’s pointer
    return (res);
}
