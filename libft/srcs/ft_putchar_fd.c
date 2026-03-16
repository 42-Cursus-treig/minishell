#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(int argc, char *argv[])
{
	char	c;
	int		fd;

	if (argc != 3)
	{
		printf("Usage: %s [char] [int]\n", argv[0]);
		return (1);
	}
	c = argv[1][0];
	fd = atoi(argv[2]);
	ft_putchar_fd(c, fd);
	printf("\n");
	return (0);
}
*/