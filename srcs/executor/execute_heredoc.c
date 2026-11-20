#include "minishell.h"

static int cleanup_temp(char **temp_file, int fd, int unlink_file) {
    if (fd != -1)
        close(fd);
    if (unlink_file && *temp_file)
        unlink(*temp_file);
    if (*temp_file) {
        free(*temp_file);
        *temp_file = NULL;
    }
    return (-1);
}

int handle_heredoc(char *delimiter, char **temp_file) {
    int fd;

    if (!delimiter || !temp_file) {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (-1);
    }
    *temp_file = create_temp_filename();
    if (!*temp_file)
        return (-1);
    fd = open(*temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        return (cleanup_temp(temp_file, -1, 0));
    if (write_heredoc_to_temp(delimiter, fd) == -1)
        return (cleanup_temp(temp_file, fd, 1));
    close(fd);
    return (0);
}

static int create_temp_file(char **temp_file) {
    int fd;

    *temp_file = create_temp_filename();
    if (!*temp_file)
        return (-1);
    fd = open(*temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("heredoc temp file");
        free(*temp_file);
        *temp_file = NULL;
        return (-1);
    }
    return (fd);
}

static void write_content_to_fd(int fd, char *content, char *delimiter) {
    char *content_copy;
    char *line_start;
    char *line_end;

    content_copy = ft_strdup(content);
    if (!content_copy)
        return;
    line_start = content_copy;
    while (line_start && *line_start) {
        line_end = strchr(line_start, '\n');
        if (line_end)
            *line_end = '\0';
        if (ft_strcmp(line_start, delimiter) == 0)
            break;
        write(fd, line_start, ft_strlen(line_start));
        if (line_end) {
            write(fd, "\n", 1);
            line_start = line_end + 1;
        } else
            line_start = NULL;
    }
    free(content_copy);
}

int handle_heredoc_with_content(char *delimiter, char **temp_file, char *content) {
    int fd;

    if (!delimiter || !temp_file || !content)
        return (handle_heredoc(delimiter, temp_file));
    fd = create_temp_file(temp_file);
    if (fd == -1)
        return (-1);
    write_content_to_fd(fd, content, delimiter);
    close(fd);
    return (0);
}
