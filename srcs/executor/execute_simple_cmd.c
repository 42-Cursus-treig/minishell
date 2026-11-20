#include "minishell.h"

static int execute_builtin_cmd(t_cmd *cmd, t_shell *shell) {
    pid_t pid;
    int status;

    if (cmd->infile || cmd->outfile || cmd->heredoc_file) {
        pid = fork();
        if (pid == 0) {
            if (setup_redirections(cmd) == -1)
                exit(1);
            exit(exec_builtin(cmd, shell));
        } else if (pid < 0) {
            perror("fork");
            return (1);
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        return (1);
    }
    return (exec_builtin(cmd, shell));
}

static int handle_file_errors(char *cmd) {
    struct stat st;

    if (stat(cmd, &st) == -1) {
        if (ft_strchr(cmd, '/'))
            printf("minishell: %s: No such file or directory\n", cmd);
        else
            printf("minishell: %s: command not found\n", cmd);
        return (127);
    }
    if (S_ISDIR(st.st_mode)) {
        printf("minishell: %s: Is a directory\n", cmd);
        return (126);
    }
    if (!(st.st_mode & S_IXUSR)) {
        printf("minishell: %s: Permission denied\n", cmd);
        return (126);
    }
    return (0);
}

static void child_process(t_cmd *cmd, t_shell *shell) {
    char *path;
    int error_code;

    if (setup_redirections(cmd) == -1)
        exit(1);
    if (!cmd->argv[0] || cmd->argv[0][0] == '\0') {
        printf("minishell: : command not found\n");
        exit(127);
    }
    path = find_command_path(cmd->argv[0], shell->envp);
    if (!path) {
        error_code = handle_file_errors(cmd->argv[0]);
        exit(error_code);
    }
    execve(path, cmd->argv, shell->envp);
    perror("execve");
    free(path);
    exit(127);
}

static int execute_external_cmd(t_cmd *cmd, t_shell *shell) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
        child_process(cmd, shell);
    else if (pid < 0) {
        perror("fork");
        return (1);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

int execute_simple_cmd(t_cmd *cmd, t_shell *shell) {
    if (!cmd->argv || !cmd->argv[0]) {
        printf("minishell: : command not found\n");
        return (127);
    }
    if (is_builtin(cmd->argv[0]))
        return (execute_builtin_cmd(cmd, shell));
    return (execute_external_cmd(cmd, shell));
}
