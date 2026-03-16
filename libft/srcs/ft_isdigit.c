#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
	if (ft_isdigit(argv[1][0]))
		printf("%c is a digit character\n", argv[1][0]);
	else
		printf("%c is not a digit character\n", argv[1][0]);
	return (0);
}
*/