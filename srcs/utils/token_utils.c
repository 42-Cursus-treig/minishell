#include "minishell.h"

static char	**expand_and_check(char **argv, t_shell *shell, int count,
	char **expanded_argv)
{
	int	i;

	i = 0;
	while (i < count)
	{
		expanded_argv[i] = expand_variables(argv[i], shell);
		if (!expanded_argv[i])
		{
			while (--i >= 0)
				free(expanded_argv[i]);
			free(expanded_argv);
			i = 0;
			while (argv[i])
				free(argv[i++]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	expanded_argv[count] = NULL;
	return (expanded_argv);
}

char	**expand_argv(char **argv, t_shell *shell)
{
	char	**expanded_argv;
	int		count;
	int		i;

	count = 0;
	if (!argv)
		return (NULL);
	while (argv[count])
		count++;
	expanded_argv = malloc(sizeof(char *) * (count + 1));
	if (!expanded_argv)
		return (NULL);
	expanded_argv = expand_and_check(argv, shell, count, expanded_argv);
	if (!expanded_argv)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (expanded_argv);
}

static void	copy_with_protection(char *dst, const char *src)
{
	while (*src)
	{
		if (*src == '$' && *(src + 1) == '\x01')
		{
			*dst++ = '$';
			src += 2;
		}
		else if (*src == '\x01')
			src++;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

char	*clean_protection_flags(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	copy_with_protection(result, str);
	return (result);
}

char	*expand_next_variable(char *str, t_shell *shell)
{
	char	*dollar_pos;
	char	*var_name;
	char	*value;
	char	*new_result;

	dollar_pos = ft_strchr(str, '$');
	while (dollar_pos && *(dollar_pos + 1) == '\x01')
		dollar_pos = ft_strchr(dollar_pos + 2, '$');
	if (!dollar_pos)
		return (str);
	var_name = get_var_name(dollar_pos + 1);
	value = get_var_value(var_name, shell);
	new_result = build_expanded_string(str, var_name, value, dollar_pos - str);
	free(str);
	free(var_name);
	free(value);
	return (new_result);
}
