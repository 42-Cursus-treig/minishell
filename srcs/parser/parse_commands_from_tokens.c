#include "minishell.h"

static int	append_cmd_to_list(t_cmd **first_cmd, t_cmd **current_cmd,
	t_cmd *new_cmd)
{
	if (!*first_cmd)
	{
		*first_cmd = new_cmd;
		*current_cmd = new_cmd;
	}
	else
	{
		(*current_cmd)->next = new_cmd;
		*current_cmd = new_cmd;
	}
	return (1);
}

t_cmd	*parse_commands_from_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;

	current = tokens;
	first_cmd = NULL;
	current_cmd = NULL;
	while (current)
	{
		new_cmd = parse_simple_cmd(&current, shell);
		if (!new_cmd)
		{
			free_tokens(tokens);
			free_cmd_list(first_cmd);
			return (NULL);
		}
		append_cmd_to_list(&first_cmd, &current_cmd, new_cmd);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (first_cmd);
}
