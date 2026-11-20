#include "minishell.h"

static int count_words(t_token *tokens) {
    int count;

    count = 0;
    while (tokens && tokens->type != TOKEN_PIPE) {
        if (tokens->type == TOKEN_WORD)
            count++;
        tokens = tokens->next;
    }
    return (count);
}

static char **copy_tokens_to_argv(t_token *tokens, int count) {
    char **argv;
    int i;

    i = 0;
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    while (tokens && tokens->type != TOKEN_PIPE && i < count) {
        if (tokens->type == TOKEN_WORD) {
            argv[i] = ft_strdup(tokens->value);
            if (!argv[i]) {
                while (--i >= 0)
                    free(argv[i]);
                free(argv);
                return (NULL);
            }
            i++;
        }
        tokens = tokens->next;
    }
    argv[count] = NULL;
    return (argv);
}

char **tokens_to_argv(t_token *tokens, t_shell *shell) {
    int i;
    int count;
    char **argv;
    char **expanded_argv;

    i = 0;
    count = count_words(tokens);
    if (count == 0)
        return (NULL);
    argv = copy_tokens_to_argv(tokens, count);
    if (!argv)
        return (NULL);
    expanded_argv = expand_argv(argv, shell);
    while (argv[i]) {
        free(argv[i]);
        i++;
    }
    free(argv);
    return (expanded_argv);
}
