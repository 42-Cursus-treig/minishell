#include "minishell.h"

static int redirect_input(char *infile) {
    int fd;

    fd = open(infile, O_RDONLY);
    if (fd == -1) {
        perror(infile);
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int redirect_output(char *outfile, int append) {
    int fd;

    if (append)
        fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror(outfile);
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int redirect_heredoc(char *heredoc_file) {
    int fd;

    if (!heredoc_file) {
        printf("minishell: heredoc: no temp file\n");
        return (-1);
    }
    fd = open(heredoc_file, O_RDONLY);
    if (fd == -1) {
        perror("heredoc");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2 heredoc");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int setup_redirections(t_cmd *cmd) {
    if (cmd->heredoc_file) {
        if (redirect_heredoc(cmd->heredoc_file) == -1)
            return (-1);
    } else if (cmd->infile) {
        if (redirect_input(cmd->infile) == -1)
            return (-1);
    }
    if (cmd->outfile && redirect_output(cmd->outfile, cmd->append) == -1)
        return (-1);
    return (0);
}
