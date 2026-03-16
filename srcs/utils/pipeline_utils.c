#include "minishell.h"

void	init_ctx(t_pipe_ctx *ctx, int cmd_count, int **pipes, pid_t *pids)
{
	ctx->cmd_count = cmd_count;
	ctx->index = 0;
	ctx->pipes = pipes;
	ctx->pids = pids;
}

int	allocate_resources(int cmd_count, pid_t **pids, int ***pipes)
{
	*pids = malloc(sizeof(pid_t) * cmd_count);
	*pipes = NULL;
	if (cmd_count > 1)
	{
		*pipes = create_pipes(cmd_count - 1);
		if (!*pipes)
		{
			free(*pids);
			return (0);
		}
	}
	if (!*pids)
	{
		if (*pipes)
			close_and_free_pipes(*pipes, cmd_count - 1);
		return (0);
	}
	return (1);
}

int	execute_command(t_shell *shell, t_pipe_ctx *ctx)
{
	ctx->pids[ctx->index] = launch_process(shell, ctx);
	if (ctx->pids[ctx->index] < 0)
	{
		if (ctx->pipes)
			close_and_free_pipes(ctx->pipes, ctx->cmd_count - 1);
		free(ctx->pids);
		return (0);
	}
	if (ctx->pipes && ctx->index < ctx->cmd_count - 1)
		close(ctx->pipes[ctx->index][1]);
	if (ctx->pipes && ctx->index > 0)
		close(ctx->pipes[ctx->index - 1][0]);
	return (1);
}

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
