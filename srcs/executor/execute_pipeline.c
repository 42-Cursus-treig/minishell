#include "minishell.h"

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

pid_t	launch_process(t_shell *shell, t_pipe_ctx *ctx)
{
	pid_t		pid;
	t_exec_ctx	exec_ctx;

	exec_ctx.prev_pipe = NULL;
	exec_ctx.curr_pipe = NULL;
	exec_ctx.is_last = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ctx->index > 0)
			exec_ctx.prev_pipe = ctx->pipes[ctx->index - 1];
		if (ctx->index < ctx->cmd_count - 1)
			exec_ctx.curr_pipe = ctx->pipes[ctx->index];
		exec_ctx.is_last = (ctx->index == ctx->cmd_count - 1);
		execute_piped_cmd(ctx->cmd, shell, &exec_ctx);
		exit(1);
	}
	else if (pid < 0)
		perror("fork");
	return (pid);
}

void	close_and_free_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

static int	wait_for_children(pid_t *pids, int n)
{
	int	status;
	int	last;
	int	i;

	last = 0;
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
			else
				last = 1;
		}
		i++;
	}
	return (last);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int			cmd_count;
	pid_t		*pids;
	int			**pipes;
	int			last_status;
	t_pipe_ctx	ctx;

	cmd_count = count_commands(cmd_list);
	if (cmd_count <= 0)
		return (1);
	if (!allocate_resources(cmd_count, &pids, &pipes))
		return (1);
	init_ctx(&ctx, cmd_count, pipes, pids);
	ctx.cmd = cmd_list;
	while (ctx.cmd)
	{
		if (!execute_command(shell, &ctx))
			return (1);
		ctx.cmd = ctx.cmd->next;
		ctx.index++;
	}
	close_all_pipes(pipes, cmd_count - 1);
	last_status = wait_for_children(pids, cmd_count);
	free_all_pipes(pipes, cmd_count - 1);
	free(pids);
	return (last_status);
}
