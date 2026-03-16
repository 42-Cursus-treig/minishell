#include "minishell.h"

void	execute_external_command(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = find_command_path(cmd->argv[0], shell->envp);
	if (!path)
		handle_command_not_found(cmd);
	if (execve(path, cmd->argv, shell->envp) == -1)
	{
		perror("execve");
		free(path);
		exit(127);
	}
	free(path);
	exit(127);
}
