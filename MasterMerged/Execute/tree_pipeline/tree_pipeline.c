#include "../execute.h"

static void cmd_add_last(t_tree *node, t_plist **head)
{
    t_plist *new_pipe_cmd;
    t_plist *curr;

    new_pipe_cmd = malloc(sizeof(t_plist));
    if (!new_pipe_cmd)
        return ;
    new_pipe_cmd->cmd_node = node;
    new_pipe_cmd->next = NULL;
    if (!*head)
        *head = new_pipe_cmd;
    else
    {
        curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_pipe_cmd;
    }
}

static void flatten_pipeline(t_tree *node, t_plist **head)
{
    t_plist *plist;

    if (!node)
        return ;
    // base case
    if (node->tok == PIPE_ID)
    {
        flatten_pipeline(node->left, head);
        flatten_pipeline(node->right, head);
    }
    else
        cmd_add_last(node, head);
}

static void free_pipe_list(t_plist *head)
{
    t_plist *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int execute_pipeline(t_tree *root, t_data *data, int input_fd)
{
    t_plist *plist;
    t_plist *curr;
    int prev;
    int fds[2];
    int status;
    pid_t last_pid;
    
    prev = input_fd;

    plist = NULL;
    flatten_pipeline(root, &plist);
    last_pid = -1;
    curr = plist;
    while (curr)
    {
        int is_pipe = curr->next != NULL;
        if (is_pipe && pipe(fds) < 0)
            return (perror("pipe"), EXIT_FAILURE);
        pid_t pid = fork();
        if (pid < 0)
            return (perror("fork"), EXIT_FAILURE);
        if (pid == 0)
        {
            if (prev != STDIN_FILENO)
                dup2(prev, STDIN_FILENO), close(prev);

            if (is_pipe)
                dup2(fds[1], STDOUT_FILENO), close(fds[0]), close(fds[1]);

            exit(recursive_execution(curr->cmd_node, data));
        }
        last_pid = pid;
        if (prev != STDIN_FILENO)
            close(prev);
        if (is_pipe)
            close(fds[1]), prev = fds[0];
        curr = curr->next;
    }
    if (prev != STDIN_FILENO)
        close(prev);
    free_pipe_list(plist);
    int w_pid = -1;
    int ex_st;
    while ((w_pid = wait(&status)) > 0)
    {
        if (w_pid == last_pid)
            ex_st = WEXITSTATUS(status);
    };
    return (ex_st);
}
