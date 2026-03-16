#include "minishell.h"

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!argv[1] || !ft_strcmp(argv[1], "~"))
	{
		path = get_env_var(shell->envp, "HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
