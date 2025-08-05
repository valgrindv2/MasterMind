# include "../execute.h"

char	*trim_edge_quotes(char *str)
{
    size_t len;

    if (!str)
        return (NULL);

    len = o_ft_strlen(str);
    if (len >= 2 && (str[0] == '\'' && str[len - 1] == '\''))
        return (ft_substr(str, 1, len - 2));
    return (ft_strdup(str)); // no trimming needed
}

void print_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        printf("argv[%d] = %s\n", i, argv[i]);
        i++;
    }
}

char *o_ft_strtrim(char *s, char *set)
{
    size_t start = 0;
    size_t end;

    if (!s || !set)
        return NULL;

    // skip leading characters in 'set'
    while (s[start] && ft_strchr(set, s[start]))
        start++;

    end = o_ft_strlen(s);
    if (end == 0)
        return ft_substr(s, 0, 0);

    end--; // move to last character

    // skip trailing characters in 'set'
    while (end > start && ft_strchr(set, s[end]))
        end--;

    // extract trimmed substring
    return ft_substr(s, start, end - start + 1);
}

char *trim_key_spaces(char *key)
{
    char *trimmed;

    if (!key)
        return (NULL);
    trimmed = o_ft_strtrim(key, " \t\n\v\f\r");
    if (!trimmed)
        return (NULL);
    return (trimmed);
}


static char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;
    char        *trimmed_key;

    cur = envlist;
    trimmed_key = trim_key_spaces(key);
    // free(key); 
    key = trimmed_key; // might have a leak , will have to revisit this.
    while (cur) 
    {
        if (ft_strcmp(key, cur->variable) == 0)
            return (ft_strdup(cur->value)); // return value
        cur = cur->next;
    }
    return (NULL);
}

static size_t   arglist_size(t_arg *arg)
{
    size_t  size;

    size = 0;
    while (arg)
    {
        size++;
        arg = arg->next;
    }
    return (size);
}
/// expand var

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
static int	count_dollars(char *s)
{
	int	i = 0;
	int	cnt = 0;

	while (s[i])
	{
		if (s[i] == '$')
			cnt++;
		i++;
	}
	return (cnt);
}

static char	**alloc_parts(char *s)
{
	int		dc = count_dollars(s);
	char	**parts;

	/* at most twice as many parts as dollars, plus terminator */
	parts = malloc(sizeof(char *) * (dc * 2 + 2));
	return (parts);
}

static int	fill_parts(char **parts, char *s, t_data *data)
{
	int	i = 0;
	int	p = 0;
	int	keylen;
	char	*seg;
	char	*val;

	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
				parts[p++] = o_ft_itoa(data->exit_status), i += 2;
			else
			{
				keylen = 0;
				while (ft_isalnum(s[i+1+keylen]) || s[i+1+keylen] == '_')
					keylen++;
				if (keylen)
				{
					seg = ft_substr(s, i + 1, keylen);
					val = find_in_env(data->env, seg);
					free(seg);
					parts[p++] = val ? val : ft_strdup("");
					i += keylen + 1;
				}
				else
					parts[p++] = ft_strdup("$"), i++;
			}
		}
		else
		{
			int	start = i;
			while (s[i] && s[i] != '$')
				i++;
			parts[p++] = ft_substr(s, start, i - start);
		}
	}
	parts[p] = NULL;
	return (p);
}

static char	*join_parts(char **parts)
{
	char	*res;

	res = list_to_string(parts);
	free_argv(parts);
	return (res);
}

char	*expand_var(char *str, t_data *data)
{
	char	**parts;
	char	*expanded;

	parts = alloc_parts(str);
	if (!parts)
		return (NULL);
	if (fill_parts(parts, str, data) < 0)
	{
		free(parts);
		return (NULL);
	}
	expanded = join_parts(parts);
	return (expanded);
}

//-----------------

static char *rewrap_inquotes(char *str)
{
    int     i;
    int     j;
    size_t  len;
    char    *new;

    len = o_ft_strlen(str);
    new = malloc ((size_t)(len + 2 + 1)); // for ' ' and \0
    if (!new)
        return (NULL);
    new[0] = '\'';
    i = 1;
    j = 0;
    while (str[j])
    {
        new[i] = str[j];
        j++;
        i++;
    }
    new[i++] = '\'';
    new[i] = '\0';
    return (new);
}

static bool still_s_quotes(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\'')
            return (true);
        i++;
    }
    return (false);
}

#include "../execute.h"

// quote_expander:
//   - walks the input one char at a time
//   - whenever it sees a single‐quote, it copies that quote,
//     then expands everything up to the next quote,
//     then copies the closing quote
//   - whenever it sees non‐quote text, it collects until the next quote
//     and runs expand_var() on that entire chunk
//   - returns a brand‐new heap buffer with all quotes and expansions
static char *quote_expander(char *str, t_data *data)
{
    int     i = 0;
    int     len = (int)o_ft_strlen(str);
    char   *result = ft_strdup("");    // start empty
    char   *tmp, *seg, *exp, *q;

    if (!result)
        return NULL;

    while (i < len)
    {
        if (str[i] == '\'')
        {

            // 1) copy the opening quote
            tmp = ft_strjoin(result, "'");
            free(result);
            result = tmp;
            i++;

            // 2) collect everything up to the next quote
            int start = i;
            while (i < len && str[i] != '\'')
                i++;
            seg = ft_substr(str, start, i - start);

            // 3) expand that segment
            exp = expand_var(seg, data);
            free(seg);

            // 4) append the expansion
            tmp = ft_strjoin(result, exp);
            free(result);
            free(exp);
            result = tmp;

            // 5) copy the closing quote, if present
            if (i < len && str[i] == '\'')
            {
                tmp = ft_strjoin(result, "'");
                free(result);
                result = tmp;
                i++;
            }
        }
        else
        {
            // Unquoted text: collect until the next quote or end
            int start = i;
            while (i < len && str[i] != '\'')
                i++;
            seg = ft_substr(str, start, i - start);

            // Expand that entire chunk at once
            exp = expand_var(seg, data);
            free(seg);

            // Append
            tmp = ft_strjoin(result, exp);
            free(result);
            free(exp);
            result = tmp;
        }
    }

    return result;
}




// core expanding function. expands the argument linked list.
int expand_list(t_arg *arg, t_data *data)
{
    t_arg   *curr;
    char    *expanded;
    char    *trimmed;

    curr = arg;
    while (curr)
    {
        if (!curr->was_s_quote) // if not literal string , meaning expandable
        {
            if (still_s_quotes(curr->value))
            {
                expanded = quote_expander(curr->value, data); // send it to quote_expander
                free(curr->value);
                curr->value = expanded;
            }
            else
            {
                expanded = expand_var(curr->value, data); // check if fails
                free(curr->value);
                curr->value = expanded;
            }
        }
        else // literal string just trim edge quotes.
        {
            trimmed = trim_edge_quotes(curr->value);
            free(curr->value);
            curr->value = trimmed;
        }
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}


// helper function.
static void print_exp_list(t_arg *arg)
{
    while (arg)
    {
        printf("[ %s ]\n", arg->value);
        printf("was single quoted [ %d ]\n", arg->was_s_quote);
        arg = arg->next;
    }
}

// Joins successive t_arg->value pieces until space_next==true
static char *join_until_space(t_arg **p_arg)
{
    t_arg *curr = *p_arg;
    char  *res = ft_strdup("");
    char  *tmp;

    if (!res)
        return NULL;

    while (curr)
    {
        tmp = ft_strjoin(res, curr->value);
        free(res);
        res = tmp;

        // if the parser marked a space after this piece, consume it and stop
        if (curr->space_next)
        {
            curr = curr->next;
            break;
        }
        // otherwise, keep joining the next piece
        curr = curr->next;
    }

    *p_arg = curr;  // advance the caller’s pointer
    return res;
}

static void    free_arg_list(t_arg *arg)
{
    t_arg   *tmp;

    if (!arg)
        return ;
    while (arg)
    {
        tmp = arg->next;
        free(arg->value);
        free(arg);
        arg = tmp;
    }
}

// entry function
char **convert_list_to_argv(t_arg *arg, t_data *data)
{
    char        **argv;
    size_t      argc;
    int         i;

    argc = arglist_size(arg);
    argv = malloc ((argc + 1)* sizeof(char *));
    if (!argv)
        return (free_arg_list(arg), NULL); // cleanup return;
    if (expand_list(arg, data) != EXIT_SUCCESS) // expanding.
        return (free_arg_list(arg), free(argv), NULL);
    i = 0;
    while(arg)
    {
        argv[i] = join_until_space(&arg);  // join as needed using space_next
        if (!argv[i])
        {
            // cleanup on failure
            while (i-- > 0) free(argv[i]);
            free(argv);
            return NULL;
        }
        i++;
    }
    argv[i] = NULL;
    return (argv);
}
