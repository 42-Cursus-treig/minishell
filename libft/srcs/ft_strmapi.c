#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
char	to_upper_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int	main(int argc, char *argv[])
{
	char	*str;
	char	*result;

	if (argc != 2)
	{
		printf("Usage: %s [str]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	result = ft_strmapi(str, to_upper_even);
	printf("Result: \"%s\"\n", result);
	free(result);
	return (0);
}
*/