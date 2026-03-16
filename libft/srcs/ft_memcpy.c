#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
/*
int	main(int argc, char *argv[])
{
	char	*dest;
	char	*str;
	size_t	n;
	void	*ptr;

	if (argc != 3)
	{
		printf("Usage: %s [str] [n]\n", argv[0]);
		return (1);
	}
	str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	n = (size_t)atoi(argv[2]);
	dest = malloc(sizeof(char) * n + 1);
	if (!str || !dest)
		return (1);
	strcpy(str, argv[1]);
	ptr = ft_memcpy(dest, str, n);
	((char *)ptr)[n] = '\0';
	printf("Result: %s\n", (char *)ptr);
	free(str);
	free(dest);
	return (0);
}
*/