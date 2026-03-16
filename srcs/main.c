#include "minishell.h"

static char	*read_input_line(void)
{
	char	*line;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		line = readline(PROMPT);
	else
		line = readline(NULL);
	if (!line)
		printf("exit\n");
	return (line);
}

static char	*extract_heredoc_content(char *line, char **cmd_line)
{
	char	*first_newline;
	char	*heredoc_content;

	*cmd_line = ft_strdup(line);
	if (!*cmd_line)
		return (NULL);
	heredoc_content = NULL;
	first_newline = strchr(*cmd_line, '\n');
	if (first_newline)
	{
		*first_newline = '\0';
		heredoc_content = ft_strdup(first_newline + 1);
	}
	return (heredoc_content);
}

static t_cmd	*process_heredoc_if_needed(char *line, t_shell *shell)
{
	char	*cmd_line;
	char	*heredoc_content;
	t_cmd	*cmd_list;

	if (ft_strstr(line, "<<"))
	{
		heredoc_content = extract_heredoc_content(line, &cmd_line);
		cmd_list = parse_line(cmd_line, shell);
		if (cmd_list && heredoc_content && cmd_list->heredoc_delim)
		{
			if (handle_heredoc_with_content(cmd_list->heredoc_delim,
					&cmd_list->heredoc_file, heredoc_content) == -1)
				cmd_list->heredoc_file = NULL;
		}
		free(cmd_line);
		if (heredoc_content)
			free(heredoc_content);
	}
	else
		cmd_list = parse_line(line, shell);
	return (cmd_list);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;
	t_cmd	*cmd_list;

	while (1)
	{
		line = read_input_line();
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			cmd_list = process_heredoc_if_needed(line, shell);
			if (cmd_list)
			{
				shell->last_status = execute_line(cmd_list, shell);
				free_cmd_list(cmd_list);
			}
		}
		free(line);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = dup_envp(envp);
	shell.last_status = 0;
	rl_variable_bind("enable-bracketed-paste", "off");
	setup_signals();
	shell_loop(&shell);
	free_envp(shell.envp);
	return (shell.last_status);
}
