#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i] && i < dsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main(int argc, char *argv[])
{
	char *dst;
	char *src;
	size_t dsize;
	size_t result;

	if (argc != 3)
	{
		printf("Usage: %s [source] [buffer_size]\n", argv[0]);
		return (1);
	}
	src = argv[1];
	dsize = atoi(argv[2]);
	dst = malloc(dsize);
	memset(dst, 'X', dsize - 1);
	dst[dsize - 1] = '\0';
	result = ft_strlcpy(dst, src, dsize);
	printf("Result: \"%s\"\n", dst);
	printf("Returned value: %zu\n", result);
	printf("Final dst length: %zu\n", strlen(dst));
	free(dst);
	return (0);
}
*/