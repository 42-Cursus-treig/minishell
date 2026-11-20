#include "minishell.h"

int count_env_vars(char **envp) {
    int count;

    count = 0;
    if (!envp)
        return (0);
    while (envp[count])
        count++;
    return (count);
}

char **dup_envp(char **envp) {
    char **new_envp;
    int count;
    int i;

    i = 0;
    count = count_env_vars(envp);
    new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return (NULL);
    while (i < count) {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i]) {
            while (--i >= 0)
                free(new_envp[i]);
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[count] = NULL;
    return (new_envp);
}

int find_env_var(char **envp, char *var) {
    int i;
    int var_len;

    i = 0;
    var_len = ft_strlen(var);
    if (!envp || !var)
        return (-1);
    while (envp[i]) {
        if (ft_strncmp(envp[i], var, var_len) == 0 && (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

char *get_env_var(char **envp, char *var) {
    int index;
    char *equals_pos;

    index = find_env_var(envp, var);
    if (index == -1)
        return (NULL);
    equals_pos = ft_strchr(envp[index], '=');
    if (equals_pos)
        return (equals_pos + 1);
    return (NULL);
}
