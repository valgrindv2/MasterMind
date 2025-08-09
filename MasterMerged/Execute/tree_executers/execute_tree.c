#include "../execute.h"

// static bool single_anon(char *str)
// {
//     if (str[0] == (char)127 && str[1] == '\0')
//         return (true);
//     return (false);
// }

// static bool still_has_anon(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == (char)127)
//             return (true);
//         i++;
//     }
//     return (false);
// }

// static int anon_index(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == (char)127)
//             return (i);
//         i++;
//     }
//     return (i); // fall back shouldnt happen.
// }

// static void init_terminator(t_ifs **args, int *i)
// {
//     *args = NULL;
//     *i = 0;
// }

// static char **terminate_inside_anons(char **argv)
// {
//     t_ifs   *args;
//     char    **new_argv;
//     char    *cut;
//     int     i;

//     init_terminator(&args, &i);
//     while (argv[i])
//     {
//         if (!single_anon(argv[i]))
//         {
//             if (still_has_anon(argv[i]))
//             {
//                 cut = ft_substr(argv[i], anon_index(argv[i]) + 1, o_ft_strlen(argv[i]));
//                 if (!cut)
//                     return (free_ifs_list(args), free_argv(argv), NULL);
//                 free(argv[i]);
//                 argv[i] = cut;
//             }
//             if (add_ifs_back(&args, argv[i]) != EXIT_SUCCESS)
//                 return (free_ifs_list(args), free_argv(argv), NULL);
//         }
//         i++;
//     }
//     new_argv = ifs_list_to_argv(args);
//     if (!new_argv)
//         return (free_ifs_list(args),  free_argv(argv), NULL);
//     return(free_ifs_list(args), free_argv(argv), new_argv);
// }

// static bool has_anons_inside(int from, int till, char **argv)
// {
//     while (from <= till)
//         if (still_has_anon(argv[from++]))
//             return (true);
//     return (false);
// }


// static bool anon(t_tree *node, size_t argc)
// {
//     if (argc == 1 && node->argv[0][0] == (char)127 && node->argv[0][1] == '\0')
//         return (true);
//     if (!has_anons_inside(0 , argc - 1, node->argv))
//         return (false);
//     node->argv = terminate_inside_anons(node->argv);
//     if (!node->argv)
//         return (true);
//     return (false);
// }


// help function with forbidden functions
// will code our own.
char    *get_absolute_path(char *cmd)
{
    char    *paths[] = {"/bin", "/usr/bin", NULL};
    char    *tmp;
    char    *full_path;
    int     i;

    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path); // Found valid path
        free(full_path);
        i++;
    }
    return (NULL); // Not found
}
//----------------------------------------------------------------------------------

int     exec_node(t_tree *node, t_data *data)
{
    int     ex_status;
    pid_t   id = fork();

    if (id == 0)
    {
            execve(get_absolute_path(node->argv[0]), node->argv, data->env_vec);
            if (node->argv[0] && node->argv[0][0] == '/') // use strchr
                dprintf(STDERR_FILENO, "Migrane: %s: No such file or directory\n", node->argv[0]); // change this to print error.
            else
                dprintf(STDERR_FILENO, "Migrane: %s: command not found\n", node->argv[0]);
            // maybe free();
            clean_up(data->head, data);
            free_argv(data->env_vec);
            free_envlist(data->env);
            exit(EXECVE_FAILURE); // exit child process if execve fails
    }
    waitpid(id, &ex_status, 0); // Parent:
    // ───── decode status ─────
    if (WIFEXITED(ex_status))
        return (WEXITSTATUS(ex_status));
    if (WIFSIGNALED(ex_status))
        return (128 + WTERMSIG(ex_status));
    return (ex_status);  // fallback (shouldn’t happen)
}

int recursive_execution(t_tree *node, t_data *data) // not static cuz used in pipeline and shortcircuit
{
    if (node->tok == COMMAND_ID) // base case exec cmd
    {
        // expand_wild_cards(node);
        if (node->red)
            if (handle_red(node, data) != EXIT_SUCCESS)
                return (EXIT_FAILURE); // restore io
        if (add_last_executed(node, data) != EXIT_SUCCESS)
            return (EXIT_FAILURE); // restore io
        if (!anon(node, arg_count(node->argv)) && node->argv[0])
        {
            if (validate_builtin(node->argv[0]))
                data->exit_status = exec_builtin(node, data);
            else
                data->exit_status = exec_node(node, data);
        }
        else
            data->exit_status = EXIT_SUCCESS;
        if (node->red)
            restore_IO(data->saved_in, data->saved_out); // if this fails check later.
        return (data->exit_status);
    }
    else if (node->tok == PIPE_ID)
    {
        data->exit_status = execute_pipeline(node, data, STDIN_FILENO);
        return (data->exit_status); // pipeline recurses back to this func
    }
    else if (node->tok == AND_ID || node->tok == OR_ID)
    {
        data->exit_status = short_circuit_operand(node, node->tok, data);
        return (data->exit_status);
    }
    if (node->left)
    {
        data->exit_status = recursive_execution(node->left, data);
        return (data->exit_status ); // go deeper left (dfs algo)
    }
    if (node->right)
    {
        data->exit_status = recursive_execution(node->right, data);
        return (data->exit_status); // when done going left go deeper right.
    }
    return (EXIT_SUCCESS); // return 0 assume no cmd to execute is success!
}

// entry point.
int execute_tree(t_tree *root, t_data *data, char **env, void *re_built)
{
    int rec_exit_status;
    if (!root)
    {
        // if (re_built != NULL) // only redirections case no commands.
        {
            // clean_up(root, data);
            // free_rebuilt(re_built);
            // return (exec_list(NULL)); // passing Null for now.
        }
        // NUllify everything.
        return (clean_up(root, data), EXIT_FAILURE);
    }
    if (merger(root, data, env) != EXIT_SUCCESS)
        return (clean_up(root, data), perror("Merge Failed"), EXIT_FAILURE);
    rec_exit_status = recursive_execution(root, data);
    return (clean_up(root, data), rec_exit_status);
}


/* to do 

 [1]  ------ handle redirections in builting [DONE]

 [2] ------ Finish Expanding ALgorithm , and edge cases [50%]

 [3] ------ Finish Export Algorithm , and integrate into Expanding [0%]

 [4] ------ Store Exit status for all commands, and integrate into echo $? [60%]
                ---> (with signals). signals left [0%]

 [5] ------ Get heredoc filedecriptor and intergate into redirections [0%]

 [6] ------ Handle executing scripts and programs that are not in PATH e.i. ./minishell [0%]

 [6.5] ---- awk not working awk '{print $3}' .

 [7] ------ Wildcard working in current directory [DONE]

*/
