#include "../execute.h"
#include <string.h>
char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;

    cur = envlist;
    while (cur)
    {
        if (o_ft_strncmp(key, cur->variable, o_ft_strlen(key)) == 0)
            return (ft_strdup(cur->value)); // return value
        cur = cur->next;
    }
    return (NULL);
}

static bool is_expandable(char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (str[i++] == '$')
            return (true);
    return (false);
}


static char *expand_variable(char *str, t_data *data)
{
    char    *expanded;
    char    **cut_list;
    char    **exp_list;
    bool    first_exp;
    int     i;
    int     count;
    size_t  len;
    char    *val;
    char    *status_temp;
    char    *status_str;

    // special case: string is exactly "$"
    if (o_ft_strncmp(str, "$", 2) == 0)
        return (ft_strdup("$"));

    cut_list = ft_split(str, '$');
    if (!cut_list)
        return (NULL);

    // count how many strings in the list for allocation
    count = 0;
    while (cut_list[count])
        count++;

    // allocate expanded list of pointers to chars char **agv.
    exp_list = malloc(sizeof(char *) * (count + 2)); // +1 for possible trailing $, if not just close it with NULL 
    if (!exp_list)
        return (free_argv(cut_list), NULL); // free previously allocated cutlist

    first_exp = (str[0] == '$'); //flag to check if first is also expandable
    i = 0;
    while (cut_list[i])
    {
        if (i == 0 && !first_exp)
            exp_list[i] = ft_strdup(cut_list[i]);
        else if (cut_list[i][0] == '\0') // just "$"
            exp_list[i] = ft_strdup("$"); // if this fails.
        else if (cut_list[i][0] == '?')
        {
            // $? is handled here
            status_str = o_ft_itoa(data->exit_status); // check if this fails.
            if (cut_list[i][0] != '\0') // [$][?][d][d][\0]  this case.
            {
                status_temp = ft_strjoin(status_str, cut_list[i] + 1); // check if this fails.
                free(status_str);
                exp_list[i] = status_temp;
            }
            else // this case [$][?][\0]
                exp_list[i] = status_str;
        }
        else
        {
            val = find_in_env(data->env, cut_list[i]);
            if (val != NULL)
                exp_list[i] = val;
            else
                exp_list[i] = ft_strdup(""); // if this fails.
        }
        i++;
    }

    // edge case if at the end there is a dollar
    len = o_ft_strlen(str);
    if (len > 0 && str[len - 1] == '$')
    {
        exp_list[i] = ft_strdup("$");  // preserve literal trailing $
        i++;
    }

    exp_list[i] = NULL; //close the list

    free_argv(cut_list);
    expanded = list_to_string(exp_list); // convert the list to one single stirng.
    free_argv(exp_list);
    return (expanded);
}



// entry function 
void expand_env_variables(t_tree *node, t_data *data)
{
    int     i;
    char    *trimmed;
    char    *edge_cleaned;
    char    *og_string;
    char    *expanded;

    i = 0;
    if (!node)
        return ;
    while (node->argv[i])
    {
        // [1] save_original.
        og_string = ft_strdup(node->argv[i]);

        // [2] trim quotes except for ['] single quote.

        // printf(YLW"[Before Trimming]===> [ %s ]"RST"\n", node->argv[i]);
        trimmed = trim_quotes(node->argv[i]);
        free(node->argv[i]);
        node->argv[i] = trimmed;
        // printf(YLW"[Trimmed]===> [ %s ]"RST"\n", node->argv[i]);

        // [3] if is expandable aand not wrapped around the og string single quotes.
        if (is_expandable(node->argv[i]) && !is_fully_single_quoted(og_string))
        {
            expanded = expand_variable(node->argv[i], data); // always check for failure.
            free(node->argv[i]);
            node->argv[i] = expanded;

        }
        
        // [4] remove edge quotes
        if (has_quotes_in_both_edges(og_string)) // only cases like '$HOME' but not '$HOME'and
        {
            edge_cleaned = trim_edge_quotes(node->argv[i]);
            free(node->argv[i]);
            node->argv[i] = edge_cleaned;
        }
        free(og_string);
        i++;
    }
}


    // loop throught the argvector 
    // detect $
    // pass through quotetrimmer
    // launch pocket insertion algorithm 
    // ----> inser the new expaned string using the environment 
    //      if env returns NULL: do nothing to the $string
    //      else expand and pocket insert
    //      return new pointer to an expanded string
    //      and free old one


    /*

        bash-3.2$ echo '$HOME' "$HOME"
        $HOME /mnt/homes/oimzilen
        bash-3.2$ echo "'$HOME' "$HOME""
        '/mnt/homes/oimzilen' /mnt/homes/oimzilen

        need to handle this edge case in expanding.
    
    */