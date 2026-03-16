#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	size_t	n;
	size_t	i;

	if (argc != 3)
	{
		printf("Usage: %s [str] [n]\n", argv[0]);
		return (1);
	}
	str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	n = (size_t)atoi(argv[2]);
	i = 0;
	if (!str)
		return (1);
	strcpy(str, argv[1]);
	ft_bzero(str, n);
	printf("Result: [");
	while (i < strlen(argv[1]))
	{
		if (str[i] == 0)
			printf("\\0");
		else
			printf("%c", str[i]);
		i++;
	}
	printf("]\n");
	free(str);
	return (0);
}
*/