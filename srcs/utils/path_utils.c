#include "minishell.h"

static int	is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return ((st.st_mode & S_IXUSR) != 0);
}

static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static char	*search_in_path_dirs(const char *cmd, char **path_dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = build_full_path(path_dirs[i], cmd);
		if (full_path && is_executable(full_path))
			return (full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	return (NULL);
}

static void	free_path_dirs(char **path_dirs)
{
	int	i;

	if (!path_dirs)
		return ;
	i = 0;
	while (path_dirs[i])
	{
		free(path_dirs[i]);
		i++;
	}
	free(path_dirs);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**path_dirs;
	char	*result;

	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_var(envp, "PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	result = search_in_path_dirs(cmd, path_dirs);
	free_path_dirs(path_dirs);
	return (result);
}
