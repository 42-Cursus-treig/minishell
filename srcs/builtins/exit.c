#include "minishell.h"

static int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_status;
	printf("exit\n");
	if (argv[1])
	{
		if (!ft_isnumeric(argv[1]))
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		if (argv[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		exit_code = ft_atoi(argv[1]);
	}
	exit(exit_code & 255);
}
