#include "minishell.h"

int count_commands(t_cmd *cmd_list) {
    int count;
    t_cmd *current;

    count = 0;
    current = cmd_list;
    while (current) {
        count++;
        current = current->next;
    }
    return (count);
}

static void setup_pipes(t_exec_ctx *ctx) {
    if (ctx->prev_pipe) {
        if (dup2(ctx->prev_pipe[0], STDIN_FILENO) == -1) {
            perror("dup2 prev_pipe read");
            exit(1);
        }
        close(ctx->prev_pipe[0]);
        close(ctx->prev_pipe[1]);
    }
    if (!ctx->is_last && ctx->curr_pipe) {
        if (dup2(ctx->curr_pipe[1], STDOUT_FILENO) == -1) {
            perror("dup2 curr_pipe write");
            exit(1);
        }
        close(ctx->curr_pipe[0]);
        close(ctx->curr_pipe[1]);
    }
}

void handle_command_not_found(t_cmd *cmd) {
    struct stat st;

    if (ft_strchr(cmd->argv[0], '/')) {
        if (stat(cmd->argv[0], &st) == -1) {
            printf("minishell: %s: No such file or directory\n", cmd->argv[0]);
            exit(127);
        }
        if (S_ISDIR(st.st_mode)) {
            printf("minishell: %s: Is a directory\n", cmd->argv[0]);
            exit(126);
        }
        if (!(st.st_mode & S_IXUSR)) {
            printf("minishell: %s: Permission denied\n", cmd->argv[0]);
            exit(126);
        }
    } else
        printf("minishell: %s: command not found\n", cmd->argv[0]);
    exit(127);
}

void execute_piped_cmd(t_cmd *cmd, t_shell *shell, t_exec_ctx *ctx) {
    int builtin_result;

    setup_pipes(ctx);
    if (!cmd || !cmd->argv || !cmd->argv[0]) {
        printf("minishell: command not found\n");
        exit(127);
    }
    if (setup_redirections(cmd) == -1)
        exit(1);
    if (is_builtin(cmd->argv[0])) {
        builtin_result = exec_builtin(cmd, shell);
        exit(builtin_result);
    }
    execute_external_command(cmd, shell);
}

int execute_line(t_cmd *cmd_list, t_shell *shell) {
    t_cmd *current;

    if (!cmd_list)
        return (0);
    current = cmd_list;
    while (current) {
        if (current->heredoc_delim && !current->heredoc_file) {
            if (handle_heredoc(current->heredoc_delim, &current->heredoc_file) == -1)
                return (1);
        }
        current = current->next;
    }
    if (!cmd_list->next)
        return (execute_simple_cmd(cmd_list, shell));
    return (execute_pipeline(cmd_list, shell));
}
