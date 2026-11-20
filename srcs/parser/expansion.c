#include "minishell.h"

static int is_var_char(char c) {
    return (ft_isalnum(c) || c == '_');
}

char *get_var_name(char *str) {
    char *var_name;
    int i;

    i = 0;
    if (str[0] == '?')
        return (ft_strdup("?"));
    while (str[i] && is_var_char(str[i]))
        i++;
    if (i == 0)
        return (NULL);
    var_name = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!var_name)
        return (NULL);
    ft_strncpy(var_name, str, i);
    var_name[i] = '\0';
    return (var_name);
}

char *get_var_value(char *var_name, t_shell *shell) {
    char *value;

    if (!var_name)
        return (ft_strdup(""));
    if (!ft_strcmp(var_name, "?")) {
        value = ft_itoa(shell->last_status);
        if (!value)
            return (ft_strdup(""));
        return (value);
    }
    value = get_env_var(shell->envp, var_name);
    if (value)
        return (ft_strdup(value));
    return (ft_strdup(""));
}

char *build_expanded_string(char *original, char *var_name, char *value, int dollar_pos) {
    char *result;
    int orig_len;
    int val_len;
    int new_len;
    int var_len;

    orig_len = ft_strlen(original);
    val_len = ft_strlen(value);
    var_len = ft_strlen(var_name);
    new_len = orig_len - (var_len + 1) + val_len;
    result = malloc(sizeof(char) * (new_len + 1));
    if (!result)
        return (NULL);
    ft_strncpy(result, original, dollar_pos);
    result[dollar_pos] = '\0';
    ft_strcat(result, value);
    ft_strcat(result, original + dollar_pos + var_len + 1);
    return (result);
}

char *expand_variables(char *str, t_shell *shell) {
    char *result;
    char *prev_result;
    char *cleaned_result;

    if (!str)
        return (NULL);
    result = ft_strdup(str);
    if (!result)
        return (NULL);
    while (1) {
        prev_result = result;
        result = expand_next_variable(result, shell);
        if (!result || result == prev_result)
            break;
    }
    cleaned_result = clean_protection_flags(result);
    free(result);
    return (cleaned_result);
}
