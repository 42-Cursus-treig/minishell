#include "libft.h"

static char	*append_buffer(char **saved, char *buffer)
{
	char	*temp;	

	if (!*saved)
		*saved = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(*saved, buffer);
		free(*saved);
		*saved = temp;
	}
	return (*saved);
}

static char	*extract_line(char **saved)
{
	char	*line;
	char	*new_pos;
	int		line_len;
	char	*temp;

	if (!*saved || !**saved)
		return (NULL);
	new_pos = ft_strchr(*saved, '\n');
	if (new_pos)
	{
		line_len = new_pos - *saved + 1;
		line = ft_substr(*saved, 0, line_len);
		temp = ft_substr(*saved, line_len, ft_strlen(*saved) - line_len);
		free(*saved);
		*saved = temp;
	}
	else
	{
		line = ft_substr(*saved, 0, ft_strlen(*saved));
		free(*saved);
		*saved = NULL;
	}
	return (line);
}

static void	cleanup_saved(char **saved)
{
	if (saved && *saved)
	{
		free(*saved);
		*saved = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*saved;
	int			bytes_read;
	char		*buffer;

	if (fd == -1)
	{
		cleanup_saved(&saved);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!saved || !ft_strchr(saved, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		append_buffer(&saved, buffer);
	}
	free(buffer);
	return (extract_line(&saved));
}
