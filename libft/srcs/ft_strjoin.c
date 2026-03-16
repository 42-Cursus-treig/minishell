#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
/*
int	main(int argc, char *argv[])
{
	char	*result;
	char	*s1;
	char	*s2;

	if (argc != 3)
	{
		printf("Usage: %s [str1] [str2]\n", argv[0]);
		return (1);
	}
	s1 = argv[1];
	s2 = argv[2];
	result = ft_strjoin(s1, s2);
	printf("Result: \"%s\"\n", result);
	printf("Length: %zu\n", strlen(result));
	free(result);
	return (0);
}
*/