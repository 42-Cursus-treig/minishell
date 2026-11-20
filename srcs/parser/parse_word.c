#include "minishell.h"

static char *create_quoted_buffer(char *line, int start, int end, char quote_char) {
    char *temp;
    int j;

    temp = malloc(sizeof(char) * ((end - start) * 2 + 1));
    if (!temp)
        return (NULL);
    j = 0;
    while (start < end) {
        temp[j++] = line[start];
        if (quote_char == '\'' && line[start] == '$')
            temp[j++] = '\x01';
        start++;
    }
    temp[j] = '\0';
    return (temp);
}

static int parse_quoted_content(char *line, int *i, char *result) {
    char quote_char;
    char *temp;
    int start;

    quote_char = line[*i];
    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != quote_char)
        (*i)++;
    if (line[*i] != quote_char)
        return (0);
    temp = create_quoted_buffer(line, start, *i, quote_char);
    if (!temp)
        return (0);
    ft_strcat(result, temp);
    free(temp);
    (*i)++;
    return (1);
}

static int parse_word_content(char *line, char *result) {
    int i;
    int len;

    i = 0;
    while (line[i] && !is_separator(line[i]) && !is_special(line[i]) && !is_newline(line[i])) {
        if (line[i] == '\'' || line[i] == '"') {
            if (!parse_quoted_content(line, &i, result))
                return (-1);
        } else {
            len = ft_strlen(result);
            result[len] = line[i];
            result[len + 1] = '\0';
            i++;
        }
    }
    return (i);
}

char *parse_word(char **line_ptr) {
    char *line;
    char *result;
    char *temp;
    int parsed_len;

    line = *line_ptr;
    result = malloc(sizeof(char) * 2000);
    if (!result)
        return (NULL);
    result[0] = '\0';
    parsed_len = parse_word_content(line, result);
    if (parsed_len == -1) {
        free(result);
        return (NULL);
    }
    *line_ptr = line + parsed_len;
    if (parsed_len == 0) {
        free(result);
        return (NULL);
    }
    temp = ft_strdup(result);
    free(result);
    return (temp);
}
