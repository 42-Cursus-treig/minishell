#include "minishell.h"

static int print_export(char **envp) {
    int i;
    char *equals_pos;

    i = 0;
    while (envp[i]) {
        printf("declare -x ");
        equals_pos = ft_strchr(envp[i], '=');
        if (equals_pos) {
            *equals_pos = '\0';
            printf("%s=\"%s\"\n", envp[i], equals_pos + 1);
            *equals_pos = '=';
        } else
            printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}

static void parse_assignment(char *arg, char **var, char **value) {
    char *equals_pos;

    equals_pos = ft_strchr(arg, '=');
    if (equals_pos) {
        *equals_pos = '\0';
        *var = arg;
        *value = equals_pos + 1;
    } else {
        *var = arg;
        *value = NULL;
    }
}

static int is_valid_identifier(char *str) {
    int i;

    if (!str || !*str)
        return (0);
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=') {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

static int handle_export_arg(char *arg, t_shell *shell) {
    char *var;
    char *value;
    char *original_arg;

    original_arg = ft_strdup(arg);
    if (!original_arg)
        return (printf("export: memory allocation failed\n"), 1);
    parse_assignment(arg, &var, &value);
    if (!is_valid_identifier(var)) {
        printf("export: `%s': not a valid identifier\n", original_arg);
        free(original_arg);
        return (1);
    }
    shell->envp = set_env_var(shell->envp, var, value);
    if (!shell->envp) {
        printf("export: memory allocation failed\n");
        free(original_arg);
        return (1);
    }
    if (value)
        *(value - 1) = '=';
    free(original_arg);
    return (0);
}

int builtin_export(char **argv, t_shell *shell) {
    int i;

    if (!argv[1])
        return (print_export(shell->envp));
    i = 1;
    while (argv[i]) {
        if (handle_export_arg(argv[i], shell))
            return (1);
        i++;
    }
    return (0);
}
