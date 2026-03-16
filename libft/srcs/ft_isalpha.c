#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
	if (ft_isalpha(argv[1][0]))
		printf("%c is a alpha character\n", argv[1][0]);
	else
		printf("%c is not a alpha character\n", argv[1][0]);		
	return (0);
}
*/