#include "minishell.h"

static t_cmd *create_cmd(void) {
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->heredoc_file = NULL;
    cmd->heredoc_delim = NULL;
    cmd->append = 0;
    cmd->next = NULL;
    return (cmd);
}

static void handle_redirection(t_token **current, t_cmd *cmd) {
    t_token *redir;

    redir = *current;
    *current = (*current)->next;
    if (!*current || (*current)->type != TOKEN_WORD)
        return;
    if (redir->type == TOKEN_REDIRECT_IN)
        set_redirection_field(&cmd->infile, (*current)->value, NULL, 0);
    else if (redir->type == TOKEN_REDIRECT_OUT)
        set_redirection_field(&cmd->outfile, (*current)->value, &cmd->append, 0);
    else if (redir->type == TOKEN_APPEND)
        set_redirection_field(&cmd->outfile, (*current)->value, &cmd->append, 1);
    else if (redir->type == TOKEN_HEREDOC)
        set_redirection_field(&cmd->heredoc_delim, (*current)->value, NULL, 0);
}

static int count_words_and_handle_redirections(t_token *tokens, t_cmd *cmd) {
    int word_count;
    t_token *current;

    word_count = 0;
    current = tokens;
    while (current && current->type != TOKEN_PIPE) {
        if (current->type == TOKEN_WORD) {
            word_count++;
            current = current->next;
        } else if (current->type >= TOKEN_REDIRECT_IN && current->type <= TOKEN_HEREDOC) {
            handle_redirection(&current, cmd);
            if (current)
                current = current->next;
        } else
            current = current->next;
    }
    return (word_count);
}

static t_cmd *create_cmd_with_argv(t_token *tokens, t_shell *shell, t_cmd *cmd) {
    int word_count;
    char **argv_temp;

    word_count = count_words_and_handle_redirections(tokens, cmd);
    if (word_count == 0)
        return (create_empty_cmd(cmd));
    argv_temp = fill_argv_from_tokens(tokens, word_count);
    if (!argv_temp)
        return (free_cmd(cmd), NULL);
    cmd->argv = expand_argv(argv_temp, shell);
    if (!cmd->argv)
        return (free_cmd(cmd), NULL);
    return (cmd);
}

t_cmd *parse_simple_cmd(t_token **tokens, t_shell *shell) {
    t_cmd *cmd;

    cmd = create_cmd();
    if (!cmd)
        return (NULL);
    cmd = create_cmd_with_argv(*tokens, shell, cmd);
    if (!cmd)
        return (NULL);
    while (*tokens && (*tokens)->type != TOKEN_PIPE)
        *tokens = (*tokens)->next;
    return (cmd);
}
