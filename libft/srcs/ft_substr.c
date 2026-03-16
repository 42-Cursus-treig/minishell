#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(int argc, char *argv[])
{
	char			*s;
	unsigned int	start;
	size_t			len;
	char			*result;

	if (argc != 4)
	{
		printf("Usage: %s [string] [start] [len]\n", argv[0]);
		return (1);
	}
	s = argv[1];
	start = atoi(argv[2]);
	len = atoi(argv[3]);
	result = ft_substr(s, start, len);
	printf("Result: \"%s\"\n", result);
	free(result);
	return (0);
}
*/