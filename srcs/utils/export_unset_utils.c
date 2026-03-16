#include "minishell.h"

static char	*create_env_var_string(char *var, char *value)
{
	char	*new_var;

	if (value)
	{
		new_var = malloc(sizeof(char)
				* (ft_strlen(var) + ft_strlen(value) + 2));
		if (!new_var)
			return (NULL);
		ft_strcpy(new_var, var);
		ft_strcat(new_var, "=");
		ft_strcat(new_var, value);
	}
	else
	{
		new_var = ft_strdup(var);
		if (!new_var)
			return (NULL);
	}
	return (new_var);
}

static char	**add_new_var_to_envp(char **envp, char *new_var_str)
{
	char	**new_envp;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
	{
		free(new_var_str);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[count] = new_var_str;
	new_envp[count + 1] = NULL;
	free(envp);
	return (new_envp);
}

char	**set_env_var(char **envp, char *var, char *value)
{
	char	*new_var_str;
	int		index;

	new_var_str = create_env_var_string(var, value);
	if (!new_var_str)
		return (NULL);
	index = find_env_var(envp, var);
	if (index != -1)
	{
		free(envp[index]);
		envp[index] = new_var_str;
		return (envp);
	}
	else
		return (add_new_var_to_envp(envp, new_var_str));
}

static char	**copy_env_without_index(char **envp, int index, int count)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * count);
	if (!new_envp)
		return (NULL);
	while (i < count)
	{
		if (i != index)
		{
			new_envp[j] = envp[i];
			j++;
		}
		else
			free(envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

char	**unset_env_var(char **envp, char *var)
{
	char	**new_envp;
	int		index;
	int		count;

	index = find_env_var(envp, var);
	count = count_env_vars(envp);
	if (index == -1)
		return (envp);
	new_envp = copy_env_without_index(envp, index, count);
	if (!new_envp)
		return (envp);
	free(envp);
	return (new_envp);
}
