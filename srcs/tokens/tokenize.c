#include "minishell.h"

t_token *create_token(t_token_type type, char *value) {
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    if (value)
        token->value = ft_strdup(value);
    else
        token->value = NULL;
    token->next = NULL;
    return (token);
}

static t_token *handle_word(char **line) {
    char *word;
    t_token *token;

    word = parse_word(line);
    if (!word)
        return (NULL);
    token = create_token(TOKEN_WORD, word);
    free(word);
    return (token);
}

static int add_token(t_token **head, t_token **current, t_token *new_token) {
    if (!new_token)
        return (0);
    if (!*head) {
        *head = new_token;
        *current = *head;
    } else {
        (*current)->next = new_token;
        *current = new_token;
    }
    return (1);
}

static void skip_spaces_and_newlines(char **line_ptr) {
    char *line;

    line = *line_ptr;
    while (*line == ' ' || *line == '\t' || *line == '\n')
        line++;
    *line_ptr = line;
}

t_token *tokenize(char *line) {
    t_token *head;
    t_token *current;
    t_token *new_token;

    head = NULL;
    current = NULL;
    new_token = NULL;
    while (*line) {
        skip_spaces_and_newlines(&line);
        if (*line == '\0')
            break;
        if (*line == '|' || *line == '<' || *line == '>')
            new_token = handle_operator(&line);
        else
            new_token = handle_word(&line);
        if (!add_token(&head, &current, new_token)) {
            free_tokens(head);
            return (NULL);
        }
    }
    return (head);
}
