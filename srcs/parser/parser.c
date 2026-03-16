#include "minishell.h"

#include "minishell.h"

static int	print_syntax_error(t_token_type type)
{
	if (type == TOKEN_PIPE)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (type == TOKEN_REDIRECT_IN)
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (type == TOKEN_REDIRECT_OUT)
		printf("minishell: syntax error near unexpected token `>'\n");
	else if (type == TOKEN_APPEND)
		printf("minishell: syntax error near unexpected token `>>'\n");
	else if (type == TOKEN_HEREDOC)
		printf("minishell: syntax error near unexpected token `<<'\n");
	else
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (2);
}

static int	check_syntax_errors(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if ((current->type >= TOKEN_REDIRECT_IN
				&& current->type <= TOKEN_HEREDOC)
			&& (!current->next || current->next->type != TOKEN_WORD))
			return (print_syntax_error(current->type));
		if (current->type == TOKEN_PIPE && !current->next)
			return (print_syntax_error(TOKEN_WORD));
		current = current->next;
	}
	return (0);
}

t_cmd	*parse_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*first_cmd;
	int		syntax_error;

	if (!line || !*line)
		return (NULL);
	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	syntax_error = check_syntax_errors(tokens);
	if (syntax_error != 0)
	{
		free_tokens(tokens);
		shell->last_status = syntax_error;
		return (NULL);
	}
	first_cmd = parse_commands_from_tokens(tokens, shell);
	free_tokens(tokens);
	return (first_cmd);
}
