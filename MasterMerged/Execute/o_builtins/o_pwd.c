#include "../execute.h"

// function entry.
int o_pwd(t_tree *node, t_data *data)
{   
    char *path;
    char pwd[PATH_MAX];
    
    if (getcwd(pwd, sizeof(pwd)))
        return (printf("%s\n", pwd), EXIT_SUCCESS);
    else if (data->pwd_reserve)
        return (printf("%s\n", data->pwd_reserve), EXIT_SUCCESS);
    else
        return (puterror("Getcwd Failed\n"), EXIT_FAILURE);
    return (EXIT_SUCCESS);
}