#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		i++;
	if (i < n)
		return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	char	*str1;
	char	*str2;
	size_t	n;
	int		res;

	if (argc != 4)
	{
		printf("Usage: %s [str1] [str2] [n]\n", argv[0]);
		return (1);
	}
	str1 = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	str2 = malloc(sizeof(char) * (strlen(argv[2]) + 1));
	n = (size_t)atoi(argv[3]);
	if ((!str1) || (!str2))
		return (1);
	strcpy(str1, argv[1]);
	strcpy(str2, argv[2]);
	res = ft_memcmp(str1, str2, n);
	printf("%d", res);
	free(str1);
	free(str2);
	return (0);
}
*/