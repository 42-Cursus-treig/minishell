#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
	if (ft_isascii(argv[1][0]))
		printf("'%s' is a ascii character\n", argv[1]);
	else
		printf("'%s' is not a ascii character\n", argv[1]);
	return (0);
}
*/