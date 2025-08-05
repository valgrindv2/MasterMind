#include "../execute.h"

int	o_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

char	*list_to_string(char **lst)
{
	char	*joined;
	char	*temp;
	size_t	i;

	i = 0;
	joined = NULL;
	while (lst[i])
	{
		temp = joined;
		joined = ft_strjoin(joined, lst[i]);
		if (!joined)
		{
			// free temp
			// return NULL
		}
		free(temp);
		i++;
	}
	return (joined);
}

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// helper function , i will get the quotes trimmed from parsing anyway (temp)
char *trim_quotes(char *str)
{
    int     i;
    int     j;
    char    quote;
    char    *result;

    if (!str)
        return (NULL);
    
    result = malloc(o_ft_strlen(str) + 1); // maximum possible size
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\"') // quote opened
        {
            quote = str[i++];
            while (str[i] && str[i] != quote) // copy inner content
                result[j++] = str[i++];
            if (str[i] == quote)
                i++; // skip closing quote
        }
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
}

// Trims only real quote marks at edges like "word" or 'word'
// But keeps literal quote characters inside


bool	has_quotes_in_both_edges(char *str)
{
    size_t  len;

    if (!str)
        return (false);

    len = o_ft_strlen(str);
    if (len < 2)
        return (false);

    if ((str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '\"' && str[len - 1] == '\"'))
        return (true);

    return (false);
}

bool is_fully_single_quoted(char *str)
{
    size_t len;

    if (!str)
        return (false);
    len = o_ft_strlen(str);
    return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}

