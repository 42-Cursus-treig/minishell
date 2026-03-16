#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
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
	ft_putstr_fd(str, fd);
	printf("\n");
	return (0);
}
*/