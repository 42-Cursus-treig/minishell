#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	char	*s1;
	char	*s2;
	size_t	n;
	int		result;

	if (argc != 4)
	{
		printf("Usage: %s [str1] [str2] [n]\n", argv[0]);
		return (1);
	}
	s1 = argv[1];
	s2 = argv[2];
	n = atoi(argv[3]);
	printf("%d\n", ft_strncmp(s1, s2, n));
	return (0);
}
*/