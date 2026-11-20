#include "minishell.h"

static int is_valid_identifier(char *str) {
    int i;

    if (!str || !*str)
        return (0);
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    i = 1;
    while (str[i]) {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

int builtin_unset(char **argv, t_shell *shell) {
    int i;

    i = 1;
    if (!argv[1])
        return (0);
    while (argv[i]) {
        if (is_valid_identifier(argv[i])) {
            shell->envp = unset_env_var(shell->envp, argv[i]);
            if (!shell->envp) {
                printf("unset: memory allocation failed\n");
                return (1);
            }
        }
        i++;
    }
    return (0);
}
