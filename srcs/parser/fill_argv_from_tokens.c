#include "minishell.h"

static int	duplicate_word_into_argv(char **argv, int *i, char *value)
{
	argv[*i] = ft_strdup(value);
	if (!argv[*i])
	{
		while (--(*i) >= 0)
			free(argv[*i]);
		free(argv);
		return (0);
	}
	(*i)++;
	return (1);
}

char	**fill_argv_from_tokens(t_token *tokens, int word_count)
{
	char	**argv;
	t_token	*current;
	int		i;

	argv = malloc(sizeof(char *) * (word_count + 1));
	if (!argv)
		return (NULL);
	current = tokens;
	i = 0;
	while (current && current->type != TOKEN_PIPE && i < word_count)
	{
		if (current->type == TOKEN_WORD)
		{
			if (!duplicate_word_into_argv(argv, &i, current->value))
				return (NULL);
		}
		else if (current->type >= TOKEN_REDIRECT_IN
			&& current->type <= TOKEN_HEREDOC)
			current = current->next;
		current = current->next;
	}
	argv[word_count] = NULL;
	return (argv);
}
