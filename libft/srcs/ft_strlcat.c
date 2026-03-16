#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (!dst || dsize == 0)
		return (src_len);
	dst_len = 0;
	while (dst[dst_len] && dst_len < dsize)
		dst_len++;
	if (dst_len >= dsize)
		return (dsize + src_len);
	i = 0;
	while (src[i] && (dst_len + i) < dsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int	main(int argc, char *argv[])
{
	char	*dst;
	char	*src;
	size_t	dsize;
	size_t	result;

	if (argc != 4)
	{
		printf("Usage: %s [destination] [source] [buffer_size]\n", argv[0]);
		return (1);
	}
	src = argv[2];
	dsize = atoi(argv[3]);
	dst = malloc(sizeof(char) * dsize);
	strncpy(dst, argv[1], dsize - 1);
	dst[dsize - 1] = '\0';
	result = ft_strlcat(dst, src, dsize);
	printf("Result: \"%s\"\n", dst);
	printf("Returned value: %zu\n", result);
	free(dst);
	return (0);
}
*/