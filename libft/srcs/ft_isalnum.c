#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
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
	if (ft_isalnum(argv[1][0]))
		printf("%c is a alphanum character\n", argv[1][0]);
	else
		printf("%c is not a alphanum character\n", argv[1][0]);		
	return (0);
}
*/