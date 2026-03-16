#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char) c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	char	c;
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
	ptr = ft_memchr(str, c, n);
	printf("%s\n", (char *)ptr);
	free(str);
	return (0);
}
*/