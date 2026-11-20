#include "minishell.h"

static t_token *create_op_token(char **line, char op, int dbl_type, int sgl_type) {
    if (*(*line + 1) == op) {
        *line += 2;
        if (op == '<')
            return (create_token(dbl_type, "<<"));
        return (create_token(dbl_type, ">>"));
    } else {
        (*line)++;
        if (op == '<')
            return (create_token(sgl_type, "<"));
        return (create_token(sgl_type, ">"));
    }
}

t_token *handle_operator(char **line) {
    if (**line == '|') {
        (*line)++;
        return (create_token(TOKEN_PIPE, "|"));
    } else if (**line == '<')
        return (create_op_token(line, '<', TOKEN_HEREDOC, TOKEN_REDIRECT_IN));
    else if (**line == '>')
        return (create_op_token(line, '>', TOKEN_APPEND, TOKEN_REDIRECT_OUT));
    return (NULL);
}
