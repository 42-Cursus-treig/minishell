#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb / 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}
/*
int	main(int argc, char *argv[])
{
	int		num;
	int		fd;

	if (argc != 3)
	{
		printf("Usage: %s [int_to_print] [int]\n", argv[0]);
		return (1);
	}
	num = atoi(argv[1]);
	fd = atoi(argv[2]);
	ft_putnbr_fd(num, fd);
	return (0);
}
*/