#include "minishell.h"

int is_separator(char c) {
    return (c == ' ' || c == '\t' || c == '\0');
}

int is_newline(char c) {
    return (c == '\n');
}

int is_special(char c) {
    return (c == '|' || c == '<' || c == '>');
}

void set_redirection_field(char **field, char *value, int *append_flag, int append_value) {
    free(*field);
    *field = ft_strdup(value);
    if (append_flag)
        *append_flag = append_value;
}

t_cmd *create_empty_cmd(t_cmd *cmd) {
    cmd->argv = malloc(sizeof(char *));
    if (!cmd->argv) {
        free_cmd(cmd);
        return (NULL);
    }
    cmd->argv[0] = NULL;
    return (cmd);
}
