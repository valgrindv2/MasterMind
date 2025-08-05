#include "execute.h"

int main(int argc, char **argv, char **env)
{
    t_data      *data; // from ayman, likely storing env, and other data.
    t_osdata    osdata;
    char        *input;
    t_cmd       *root;

    // init_data_struct(&data, env); // segfaults in mac
    osdata.env = env;
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1334)
    {
        input = readline(BLU"Master@Mind> "RST);

        if (!input)
        {
            return (printf("exit\n"), free(input), EXIT_SUCCESS); // handling ctrl-D
        }
        if (input[0])
            add_history(input); // add non-empty strings to history.
        root = o_tokenizer(input, &osdata);
        // print_tree(root); // printer debugger (remove later)
        execute_tree(root, &osdata);
        free(input);
    }
    return (EXIT_SUCCESS);
}

// int main(void)
// {
//     t_cmd   *root;
//     t_cmd   *leaf1;
//     t_cmd   *leaf2;

// //                              ||
// //                            /    \
// //                          &&     echo hi
// //                        /    \
// //                     ls -l  echo test

//     // 1st lvl
//     root = create_leaf("||", O_OR);
//     // 2nd lvl
//     leaf1 = add_left(&root ,"&&", O_AND);
//     leaf2 = add_right(&root, "/bin/echo hi", O_CMD);
//     // 3rd lvl
//     add_left(&leaf1, "/bin/ls -l", O_CMD);
//     add_right(&leaf1, "/bin/echo test", O_CMD);
    

//     puts("tree created!");
//     execute_tree(&root);
//     // puts("tree executed");

//     return (EXIT_SUCCESS);
// }



