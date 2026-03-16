#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
int	main(int argc, char *argv[])
{
	int	character;
	int	result;

	if (argc != 2)
	{
		printf("Usage: %s [char]\n", argv[0]);
		return (1);
	}
	character = argv[1][0];
	printf("Input character: '%c' (ASCII: %d)\n", character, character);
	result = ft_toupper(character);
	printf("Result: '%c' (ASCII: %d)\n", result, result);
	return (0);
}
*/