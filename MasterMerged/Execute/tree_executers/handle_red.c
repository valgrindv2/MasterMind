#include "../execute.h"

bool    has_ambig_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ' || str[i] == '\t' 
            || str[i] == (char)1 || str[i] == (char)127)
            return (true);
        i++;
    }
    return (false);
}

static bool expandable_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

static bool has_ifs(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (char)1)
            return (true);
        i++;
    }
    return (false);
}

static int red_in(t_red *red, t_data *data)
{
    int in_fd;

    in_fd = open(red->value, O_RDONLY);
    if (in_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(in_fd, STDIN_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(in_fd), EXIT_FAILURE);
    close(in_fd);
    return (EXIT_SUCCESS);
}

static int red_out(t_red *red, t_data *data)
{
    int out_fd;

    out_fd = open(red->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(out_fd, STDOUT_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(out_fd), EXIT_FAILURE);
    close(out_fd);
    return (EXIT_SUCCESS);
}

static int  red_append(t_red *red, t_data *data)
{
    int out_fd;

    out_fd = open(red->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (out_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(out_fd, STDOUT_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(out_fd), EXIT_FAILURE);
    close(out_fd);
    return (EXIT_SUCCESS);
}



int read_file(t_red *red, char **joined)
{
    char    *file;
    char    *tmp;

    file = get_next_line(red->fd_here_doc);
    while (file)
    {
        tmp = *joined;
        *joined = gnl_ft_strjoin(*joined, file);
        if (!*joined)
        {
            // garbage
            free(tmp);
            free(file);
            return (EXIT_FAILURE);
        }
        free(tmp); // garabge
        free(file);
        file = get_next_line(red->fd_here_doc);
    }
    return (EXIT_SUCCESS);
}

char    *expand_heredoc(char *joined, t_red *red, t_data *data)
{
    char    *expanded;

    if (!red->was_d_quote && !red->was_s_quote)
    {
        expanded = expand_var(joined, data, true);
        free(joined);
    }
    else
        expanded = joined;
    return (expanded);
}



int red_here_doc(t_red *red, t_data *data)
{
    char *file;
    char *joined ;
    char *expanded;
    int   pipefd[2];

    if (red->fd_here_doc == -1)
        return (EXIT_SUCCESS);
    joined = NULL;
    read_file(red, &joined);
    if (!joined)
        joined = ft_strdup("");
    expanded = expand_heredoc(joined, red, data);
    if (pipe(pipefd) == -1)
        return (perror("pipe"), EXIT_FAILURE);
    write(pipefd[1], expanded, o_ft_strlen(expanded));
    close(pipefd[1]); // Close write end
    free(expanded); // garbage...
    close(red->fd_here_doc);
    red->fd_here_doc = pipefd[0];
    if (dup2(red->fd_here_doc, STDIN_FILENO) == -1)
        return (perror("dup2"), EXIT_FAILURE);
    close(red->fd_here_doc);
    red->fd_here_doc = -1;
    return (EXIT_SUCCESS);
}


static bool check_expanded_malloc(char **expanded, t_data *data, t_red *curr_red)
{
    if (curr_red->was_s_quote)
        *expanded = ft_strdup(curr_red->value);
    else if (curr_red->was_d_quote)
        *expanded = expand_var(curr_red->value, data, true); // removed normalize ifs
    else
        *expanded = expand_var(curr_red->value, data, false);
    if (!*expanded)
            return(EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static void init_red(t_data *data, t_tree *node, t_red  **curr_red)
{
    data->saved_in = dup(STDIN_FILENO); // check
    data->saved_out = dup(STDOUT_FILENO); // check
    *curr_red = node->red;
}

static int  redirect_current(t_red *curr_red, t_data *data)
{
    if (curr_red->tok == INPUT_FILE_ID)
    {
        if (red_in(curr_red, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    else if (curr_red->tok == OUTPUT_FILE_ID)
    {
        if (red_out(curr_red, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    else if (curr_red->tok == INPUT_APP_FILE_ID)
    {
        if (red_append(curr_red, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    else if(curr_red->tok == DEL_ID)
    {
        if (red_here_doc(curr_red, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static bool ambig_wrapper(char *str, bool ambig_dollar, bool dquoted)
{
    if (!ambig_dollar)
        return (false);
    if (!dquoted && has_ambig_space(str))
        return (true);
    if (!dquoted && str[0] == ANON)
        return (true);
    return (false);
}

int handle_red(t_tree *node, t_data *data)
{
    t_red   *curr_red;
    char    *expanded;
    bool    ambig;
    char    *og;
    char    *cleaned;

    init_red(data, node, &curr_red);
    while (curr_red)
    {
        ambig = expandable_check(curr_red->value);
        og = ft_strdup(curr_red->value);
        if (check_expanded_malloc(&expanded, data, curr_red) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
        free(curr_red->value);
        curr_red->value = expanded;
        if (curr_red->tok != DEL_ID && ambig_wrapper(curr_red->value, ambig, curr_red->was_d_quote))
            return (dprintf(2 , RED"Master@Mind: %s: ambiguous redirect\n"RST, og), EXIT_FAILURE);
        cleaned = red_ifs_pass(curr_red->value);
        if (!cleaned)
            return (free(og), free(curr_red->value), EXIT_FAILURE);
        free(curr_red->value);
        curr_red->value = cleaned;
        if (redirect_current(curr_red, data) != EXIT_SUCCESS)
            return (data->exit_status = EXIT_FAILURE, EXIT_FAILURE);
        free(og);
        curr_red = curr_red->next;
    }
    return (EXIT_SUCCESS);
}

void    restore_IO(int saved_in, int saved_out, bool no_red)
{
    if (no_red)
        return ;
    // Always restore STDIN/STDOUT
    dup2(saved_in, STDIN_FILENO);
    dup2(saved_out, STDOUT_FILENO);
    close(saved_in);
    close(saved_out);
}
