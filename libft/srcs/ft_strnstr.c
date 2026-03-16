#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	len_n;
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	if (ft_strlen(needle) == 0)
		return ((char *) haystack);
	len_n = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < n)
			j++;
		if (j == len_n)
			return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	char	*haystack;
	char	*needle;
	size_t	n;
	char	*result;

	if (argc != 4)
	{
		printf("Usage: %s [haystack] [needle] [n]\n", argv[0]);
		return (1);
	}
	haystack = argv[1];
	needle = argv[2];
	n = atoi(argv[3]);
	result = ft_strnstr(haystack, needle, n);
	if (result)
		printf("Substring found: \"%s\"\n", result);
	else
		printf("Needle not found\n");
	return (0);
}
*/