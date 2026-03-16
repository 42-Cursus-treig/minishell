#include "minishell.h"

char	*create_temp_filename(void)
{
	static int	heredoc_counter = 0;
	char		*filename;
	int			base_len;

	filename = malloc(sizeof(char) * 50);
	if (!filename)
		return (NULL);
	ft_strcpy(filename, "/tmp/.minishell_heredoc");
	base_len = ft_strlen(filename);
	if (heredoc_counter < 26)
	{
		filename[base_len] = 'a' + heredoc_counter;
		filename[base_len + 1] = '\0';
	}
	else
		filename[base_len] = '\0';
	heredoc_counter = (heredoc_counter + 1) % 26;
	return (filename);
}

char	*read_heredoc_line(void)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (NULL);
	return (line);
}

int	write_heredoc_to_temp(char *delimiter, int fd)
{
	char	*line;

	line = read_heredoc_line();
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = read_heredoc_line();
	}
	return (0);
}

void	cleanup_heredoc_temp(char *temp_file)
{
	if (temp_file)
	{
		unlink(temp_file);
		free(temp_file);
	}
}
