#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	int		c;
	size_t	n;
	void	*ptr;

	if (argc != 4)
	{
		printf("Usage: %s [str] [char] [n]\n", argv[0]);
		return (1);
	}
	str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	c = argv[2][0];
	n = (size_t)atoi(argv[3]);
	if (!str)
		return (1);
	strcpy(str, argv[1]);
	ptr = ft_memset(str, c, n);
	printf("%s\n", (char *)ptr);
	free(str);
	return (0);
}
*/