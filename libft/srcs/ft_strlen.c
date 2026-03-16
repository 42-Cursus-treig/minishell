#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [str]\n", argv[0]);
		return (1);
	}
	printf("Length of %s is %ld\n", argv[1], ft_strlen(argv[1]));
	return (0);
}
*/