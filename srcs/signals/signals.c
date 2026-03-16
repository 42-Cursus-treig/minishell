#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
