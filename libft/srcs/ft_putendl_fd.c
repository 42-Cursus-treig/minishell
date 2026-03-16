#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	int		fd;

	if (argc != 3)
	{
		printf("Usage: %s [str] [int]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	fd = atoi(argv[2]);
	ft_putendl_fd(str, fd);
	return (0);
}
*/