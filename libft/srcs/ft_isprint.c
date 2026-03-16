#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [char]\n", argv[0]);
		return (1);
	}
	if (ft_isprint(argv[1][0]))
		printf("'%s' is a printable character\n", argv[1]);
	else
		printf("'%s' is not a printable character\n", argv[1]);
	return (0);
}
*/