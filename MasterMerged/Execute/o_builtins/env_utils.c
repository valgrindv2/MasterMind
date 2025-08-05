#include "../execute.h"

char *get_env_value(char *variable, char **env)
{
    int i = 0;
    int len = ft_strlen(variable);

    while (env[i])
    {
        if (ft_strncmp(env[i], variable, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1); // skip "variable="
        i++;
    }
    return (""); // not found return empty string.
}
